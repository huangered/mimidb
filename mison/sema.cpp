#include "sema.hpp"
#include <string>
#include <functional>
#include <cstring>
#include "debug.hpp"
#include "symtab.hpp"

static std::string join(const SymbolList& v);
static std::string join2(const std::vector<int>& v);

struct group_key {
    int dot;
    Symbol left;
    SymbolList right;

    bool operator<(const group_key& other) const;
};

bool
group_key::operator<(const group_key& g1) const {
    int i{ 0 };

    if ((i = dot - g1.dot) != 0) {
        return i < 0 ? true : false;
    }
    if ((i = left->id - g1.left->id) != 0) {
        return i < 0 ? true : false;
    }

    return SymbolListLess(right, g1.right);
}

// end

SemaParser::SemaParser()
    : _maxState{ 0 } {
    _firstSet  = std::unique_ptr<FirstSet>(new FirstSet());
    _stateList = std::unique_ptr<StateCollection>(new StateCollection());
    _stateList->Add(new StateData{ 0 });

    for (Rule rule : Rules) {
        Item r        = new ItemData{};
        r->id         = rule->id;
        r->left       = rule->left;
        r->right      = rule->right;
        r->func_block = rule->funcBlock;
        r->root       = rule->root;
        _rules.push_back(r);
    }

    Item rule = _rules[_rules.size() - 1]->Clone();
    rule->SetToken(Symtab::eof->id);
    _stateList->Add(0, rule);
}

SemaParser::~SemaParser() {
    for (Item r : _rules) {
        delete r;
    }
}

void
SemaParser::SetTypeMap(const std::map<std::string, std::string>& _typeMap) {
    this->_typeMap = _typeMap;
}

void
SemaParser::GenerateParseTable(void) {
    _firstSet->Gen();
    _firstSet->Print();
    for (int i{}; i < _stateList->Size(); i++) {
        if (_stateList->IsEmpty(i)) {
            break;
        }

        handleState(i);
    }

#ifdef _log_
    printf("state list:\n");
    for (int i{}; i < _stateList->Size(); i++) {
        if (_stateList->IsEmpty(i)) {
            break;
        }
        printf("state %d\n", i);
        for (Item r : _stateList->GetRules(i)) {
            auto r_str = join(r->right);
            auto t_str = join2(r->tokens);
            printf("     %d => %s [ %s ] (%d) ", r->left, r_str.c_str(), t_str.c_str(), r->dot);

            if (!r->IsDotEnd()) {
                printf("next %d", r->next_state);
            }

            printf("\n");
        }
    }
#endif
    generateTable();
}

// === private part ===
void
SemaParser::handleState(int stateId) {
    State state = _stateList->GetState(stateId);
    // 1. 扩展规则
    expandRules(state);
    // 2. 构建新状态
    std::map<int, Symbol> tokens;
    for (Item rule : state->GetItems()) {
        if (!rule->IsDotEnd()) {
            Symbol token      = rule->GetTokenAfterDot();
            tokens[token->id] = token;
        }
    }

    for (auto iter = tokens.begin(); iter != tokens.end(); iter++) {
        Symbol token = iter->second;

        ItemList movedRules;
        ItemList newStateRules;
        for (Item r : state->GetItems()) {
            if (!r->IsDotEnd() && r->right[r->dot]->id == token->id) {
                movedRules.push_back(r);

                Item n = r->Clone();
                n->dot++;
                newStateRules.push_back(n);
            }
        }

        // 寻找相同的状态集合。
        State sameState = searchSameState(newStateRules);

        if (sameState == nullptr) {
            // 没找到
            _maxState++;
            std::for_each(movedRules.begin(), movedRules.end(), [&](Item r) { r->next_state = _maxState; });
            if (_stateList->Size() <= _maxState) {
                for (int i = _stateList->Size(); i <= _maxState; i++) {
                    _stateList->Add(new StateData(i));
                }
            }
            for (Item newRule : newStateRules) {
                _stateList->GetState(_maxState)->Add(newRule);
            };
        } else {
            // 找到了
            for (Item r : movedRules) {
                r->next_state = sameState->GetId();
            }
        }
    }
}

void
SemaParser::generateTable(void) {
    _gotoTable   = std::unique_ptr<GotoTable>(new GotoTable(_stateList->Size(), Symtab::nsym - Symtab::ntoken()));
    _actionTable = std::unique_ptr<ActionTable>(new ActionTable(_stateList->Size(), Symtab::ntoken()));

    for (int stateId{}; stateId < _stateList->Size(); stateId++) {
        for (Item r : _stateList->GetRules(stateId)) {
            if (r->IsDotEnd()) {
                // find rule id
                // add r1 in action
                for (int ruleId{}; ruleId < _rules.size(); ruleId++) {
                    Item c = _rules[ruleId];
                    if (c->left == r->left && SymbolListEqual(c->right, r->right)) {
                        for (int token : r->GetTokens()) {
                            _actionTable->AddRule(stateId, token, ruleId, r->root);
                        }
                    }
                }
            } else {
                Symbol token = r->right[r->dot];
                if (token->clazz == nterm) {
                    // update goto
                    _gotoTable->Add(stateId, token->id - Symtab::ntoken(), r->next_state);
                } else {
                    // update action
                    _actionTable->Add(stateId, token->id, r->next_state);
                }
            }
        }
    }

    _actionTable->Print();
    _gotoTable->Print();
}

void
SemaParser::expandRules(State state) {
    int count = 0;

    for (;;) {
        count = 0;
        std::set<Item> copied;

        for (Item r : state->GetItems()) {
            if (r->IsDotEnd()) {
                continue;
            }
            Symbol word = r->GetTokenAfterDot();
            if (word->clazz == nterm) {
                // non terminals
                // update state list
                auto rule_left_id_eq = [word](Item rule) -> bool { return rule->left == word->id; };
                ItemList match;
                find_all(_rules, match, rule_left_id_eq);
                for (Item rule : match) {
                    SymbolList tokenList    = r->GetStringAfterDot();
                    std::vector<int> tokens = _firstSet->Find(tokenList, r->GetTokens());
                    // todo: 这里可以优化这个lazy clone
                    Item copy = rule->Clone();
                    copy->dot = 0;
                    copy->SetTokens(tokens);
                    // 如果是新rule
                    auto rule_eq = [copy](Item rule) -> bool { return *rule == *copy; };
                    ItemList src = state->GetItems();
                    ItemList dest;
                    find_all(src, dest, rule_eq);
                    if (dest.empty()) {
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

    ItemList tmp;
    std::multimap<group_key, Item, std::less<group_key>> gg;

    // 合并 state 里的 rules
    for (Item rule : state->GetItems()) {
        auto check_exist = [rule](Item r) -> bool {
            return r->dot == rule->dot && r->left == rule->left && SymbolListEqual(r->right, rule->right);
        };

        auto iter = std::find_if(tmp.begin(), tmp.end(), check_exist);
        if (iter != tmp.end()) {
            Item r = *iter;
            r->AppendTokens(rule->tokens);
        } else {
            tmp.push_back(rule->Clone());
        }
    }
    state->ResetItems(tmp);
    std::for_each(tmp.begin(), tmp.end(), [](Item r) { delete r; });
}

State
SemaParser::searchSameState(const ItemList& newStateRules) {
    int max{ _stateList->Size() };
    for (int i{ 0 }; i < max; i++) {
        State state = _stateList->GetState(i);
        if (state->MatchItem(newStateRules)) {
            return state;
        }
    }
    return nullptr;
}

std::string
join(const SymbolList& v) {
    std::string a;
    for (Symbol t : v) {
        if (t->clazz == nterm) {
            a += t->name;
            a += ",";
        } else {
            a += std::to_string(Symtab::GetId(t->name));
            a += ",";
        }
    }
    return a;
}

std::string
join2(const std::vector<int>& v) {
    std::string a;
    for (int t : v) {
        a += std::to_string(t);
        a += ",";
    }
    return a;
}

std::string
SemaParser::funcReplace(const Item rule) {

    std::string tmp = rule->func_block;
    for (int i = rule->right.size() - 1; i >= 0; i--) {
        std::string name = this->_typeMap[rule->right[i]->name];
        std::string w    = "$" + std::to_string(i);
        std::string r    = "(child[" + std::to_string(i);
        r += "].";
        r += name;
        r += ")";
        std::size_t pos;
        while ((pos = tmp.find(w)) != std::string::npos)
            tmp.replace(pos, w.size(), r);
    }
    std::size_t pos;

    std::string name = Symtab::GetName(rule->left);

    while ((pos = tmp.find("$$")) != std::string::npos) {
        name = "(item." + this->_typeMap[name] + ")";
        tmp.replace(pos, 2, name);
    }

    return tmp;
}
