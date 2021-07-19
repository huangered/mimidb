#include "sema/sema.hpp"
#include <string>

std::ostream&
operator<<(std::ostream& os, const RecordData& dt) {
    if (dt.id == -1) {
        os << "  ";
        return os;
    }
    if (dt.acc) {
        os << "acc";
        return os;
    }
    if (dt.state) {
        os << "s" << dt.id;
    } else {
        os << "r" << dt.id;
    }
    return os;
}

static bool SemaTokenListEqual(SemaTokenList& left, SemaTokenList& right);
static std::string join(const SemaTokenList& v);
static std::string join2(const std::vector<Tok>& v);

StateCollection::~StateCollection() {
    for (State state : stateList) {
        delete state;
    }
}

int
StateCollection::Size() {
    return stateList.size();
}

bool
StateCollection::IsEmpty(int stateId) {
    return stateList[stateId]->GetRules().size() == 0;
}

void
StateCollection::Add(State state) {
    stateList.push_back(state);
}

void
StateCollection::Add(int stateId, Rule rule) {
    stateList[stateId]->Add(rule);
}

RuleList
StateCollection::GetRules(int stateId) {
    return stateList[stateId]->GetRules();
}

State
StateCollection::GetState(int stateId) {
    return stateList[stateId];
}

// end

Parser::Parser(std::vector<SimpleRule> rules) {
    _maxState = 0;
    _firstSet = new FirstSet(rules);
    _stateList = new StateCollection();
    _stateList->Add(new StateData{0});
    _gotoTable = nullptr;
    _actionTable = nullptr;

    for (SimpleRule rule : rules) {
        Rule r = new RuleData{};
        r->id = rule->id;
        r->left = rule->left;
        r->right = rule->right;
        _rules.push_back(r);
    }
    _rules[0]->root = true;
    Rule rule = _rules[0]->Clone();
    rule->SetToken(Tok::Eof);
    _stateList->Add(0, rule);
}

Parser::~Parser() {
    delete _gotoTable;
    delete _actionTable;
    delete _firstSet;
    delete _stateList;
}

void
Parser::GenerateParseTable(void) {
    _firstSet->Gen();
    _firstSet->Print();
    for (int i = 0; i < _stateList->Size(); i++) {
        if (_stateList->IsEmpty(i)) {
            break;
        }

        handleState(i);
    }

    for (int i = 0; i < _stateList->Size(); i++) {
        if (_stateList->IsEmpty(i)) {
            break;
        }
        std::cout << "state " << i << std::endl;
        for (Rule r : _stateList->GetRules(i)) {
            std::cout << r->left->name << " => " << join(r->right);
            std::cout << " " << join2(r->tokens);
            std::cout << " " << r->dot << " ";

            if (!r->IsDotEnd()) {
                std::cout << "next " << r->next_state;
            }

            std::cout << std::endl;
        }
    }

    generateTable();
}

Node
Parser::Parse(std::vector<LexToken> input) {
    bool acc  = false;
    Node node = nullptr;
    // init stack
    std::stack<int> state_stack;
    std::stack<Node> token_stack;
    std::stack<LexToken> input_stack;

    state_stack.push(0);

    for (auto iter = input.rbegin(); iter != input.rend(); iter++) {
        input_stack.push(*iter);
    }

    while (!acc) {
        bool op = eatToken(state_stack, token_stack, input_stack, &acc);

        if (!op) {
            std::cout << "no action" << std::endl;
            break;
        }
    }

    node = token_stack.top();

    return node;
}

// === private part ===
void
Parser::handleState(int stateId) {
    State state = _stateList->GetState(stateId);
    // 1. 扩展规则
    expandRules(state);
    // 2. 构建新状态
    std::map<int, SemaToken> tokens;
    for (Rule rule : state->GetRules()) {
        if (!rule->IsDotEnd()) {
            SemaToken token = rule->GetTokenAfterDot();
            tokens[token->id] = token;
        }
    }

    for (auto iter = tokens.begin(); iter != tokens.end(); iter++) {
        SemaToken token = iter->second;

        RuleList movedRules;
        RuleList newStateRules;
        for (Rule r : state->GetRules()) {
            if (!r->IsDotEnd() && r->right[r->dot]->id == token->id) {
                movedRules.push_back(r);

                Rule n = r->Clone();
                n->dot++;
                newStateRules.push_back(n);
            }
        }

        // 寻找相同的状态集合。
        State sameState = searchSameState(newStateRules);

        if (sameState == nullptr) {
            // 没找到
            _maxState++;
            std::for_each(movedRules.begin(), movedRules.end(), [&](Rule r) { r->next_state = _maxState; });
            if (_stateList->Size() <= _maxState) {
                for (int i = _stateList->Size(); i <= _maxState; i++) {
                    _stateList->Add(new StateData(i));
                }
            }
            for (Rule newRule : newStateRules) {
                _stateList->GetState(_maxState)->Add(newRule);
            };
        } else {
            // 找到了
            for (Rule r : movedRules) {
                r->next_state = sameState->GetId();
            }
        }
    }
}

void
Parser::generateTable(void) {
    _gotoTable = new GotoTable(_stateList->Size(), _maxState);
    _actionTable = new ActionTable(_stateList->Size(), Tok::unknown);

    for (int i = 0; i < _stateList->Size(); i++) {
        for (Rule r : _stateList->GetRules(i)) {
            if (r->IsDotEnd()) {
                // find rule id
                // add r1 in action
                for (int g = 0; g < _rules.size(); g++) {
                    Rule c = _rules[g];
                    if (c->left->id == r->left->id && SemaTokenListEqual(c->right, r->right)) {
                        for (Tok token : r->GetTokens()) {
                            _actionTable->AddRule(i, token, g, r->root);
                        }
                    }
                }
            } else {
                SemaToken w = r->right[r->dot];
                if (w->sema) {
                    // update goto
                    _gotoTable->Add(i, w->id, r->next_state);
                } else {
                    // update action
                    _actionTable->Add(i, w->lexToken->tok, r->next_state);
                }
            }
        }
    }
    _actionTable->Print();
    _gotoTable->Print();
}

void
Parser::expandRules(State state) {
    int count = 0;

    for (;;) {
        count = 0;
        std::set<Rule> copied;

        for (Rule r : state->GetRules()) {
            r->cur_state = state->GetId();
            if (r->IsDotEnd()) {
                continue;
            }
            SemaToken word = r->GetTokenAfterDot();
            if (word->sema) {
                // non terminals
                // update state list

                auto rule_left_id_eq = [word](Rule rule) -> bool { return rule->left->id == word->id; };
                RuleList match;
                find_all(_rules, match, rule_left_id_eq);
                for (Rule rule : match) {
                    std::vector<Tok> tokens = _firstSet->Find(r->GetStringAfterDot(), r->GetTokens());

                    Rule copy = rule->Clone();
                    copy->dot = 0;
                    copy->SetTokens(tokens);
                    // 如果是新rule
                    auto rule_eq = [copy](Rule rule) -> bool { return rule->Compare(*copy) == 0; };
                    RuleList src = state->GetRules();
                    RuleList dest;
                    find_all(src, dest, rule_eq);
                    if (dest.size() == 0) {
                        copied.insert(copy);
                        count++;
                    } else {
                        delete copy;
                    }
                }
            }
        }

        if (count == 0) {
            break;
        } else {
            state->Add(copied);
        }
    }

    RuleList tmp;

    // 合并 state 里的 rules
    for (Rule rule : state->GetRules()) {
        auto check_exist = [rule](Rule r) -> bool {
            return r->dot == rule->dot && r->left->id == rule->left->id && SemaTokenListEqual(r->right, rule->right);
        };

        auto iter = std::find_if(tmp.begin(), tmp.end(), check_exist);
        if (iter != tmp.end()) {
            Rule r = *iter;
            r->AppendTokens(rule->tokens);
            // todo: 要delete多余的rule；
            delete r;
            *iter = nullptr;
        } else {
            tmp.push_back(rule);
        }
    }
    state->ResetRules(tmp);
}

State
Parser::searchSameState(RuleList newStateRules) {
    for (int i{0}; i < _stateList->Size(); i++) {
        State state = _stateList->GetState(i);
        if (state->MatchRule(newStateRules)) {
            return state;
        }
    }
    return nullptr;
}

bool
Parser::reduce(std::stack<int>& states, std::stack<Node>& syms, Record curRecord) {
    bool op        = false;
    Node curNode   = syms.top();
    Record record  = curRecord;
    int curStateId = states.top();

    if (record != nullptr && !record->state) {
        op        = true;
        Rule rule = _rules[record->id];
        std::vector<Node> child;
        for (int i = 0; i < rule->right.size(); i++) {
            child.push_back(syms.top());
            syms.pop();
            states.pop();
        }

        Node left = rule->Format(rule->left, child);
        syms.push(left);

        // find goto table
        curStateId = states.top();

        int nextStateId = _gotoTable->Find(curStateId, rule->left->id)->id;
        states.push(nextStateId);
    }
    return op;
}

bool
Parser::eatToken(std::stack<int>& states, std::stack<Node>& syms, std::stack<LexToken>& input, bool* acc) {
    bool op        = false;
    int curStateId = states.top();
    LexToken token = input.top();
    Record record  = _actionTable->Find(curStateId, token->tok);
    if (record != nullptr) {
        op = true;

        if (record->acc) {
            *acc = true;
            return true;
        }

        if (record->state) {
            states.push(record->id);
            syms.push(new NodeData(token));
            input.pop();
            return op;
        } else {
            return reduce(states, syms, record);
        }
    }
    return op;
}

std::string
join(const SemaTokenList& v) {
    std::string a;
    for (SemaToken t : v) {
        if (t->sema) {
            a += t->name;
            a += ",";
        } else {
            a += t->lexToken->name;
            a += ",";
        }
    }
    return a;
}

std::string
join2(const std::vector<Tok>& v) {
    std::string a;
    for (Tok t : v) {
        a += t;
        a += ",";
    }
    return a;
}

bool
SemaTokenListEqual(SemaTokenList& left, SemaTokenList& right) {
    if (left.size() != right.size()) {
        return false;
    }

    auto cmp = [](const SemaToken l, const SemaToken r) { return l->id < r->id; };

    std::sort(left.begin(), left.end(), cmp);

    std::sort(right.begin(), right.end(), cmp);

    for (int i{0}; i < left.size(); i++) {
        if (left[i]->id != right[i]->id) {
            return false;
        }
    }

    return true;
}