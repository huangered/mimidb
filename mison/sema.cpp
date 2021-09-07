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

    Item rootRule;

    for (Rule rule : Rules) {
        Item item  = new ItemData{};
        item->rule = rule;
        item->id   = rule->id;
        _rules.push_back(item);

        if (ItemRoot(item)) {
            rootRule = item->Clone();
            rootRule->SetToken(Symtab::eof->id);
        }
    }

    _stateList->Add(0, rootRule);
}

SemaParser::~SemaParser() {
    for (Item item : _rules) {
        delete item;
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
        printf("state %d:\n", i);
        for (Item item : _stateList->GetRules(i)) {
            auto r_str = join(ItemRights(item));
            auto t_str = join2(item->tokens);
            printf("     %s => %s [ %s ] (%d) ", Symtab::GetName(ItemLeft(item)).c_str(), r_str.c_str(), t_str.c_str(),
                   item->dot);

            if (!item->IsDotEnd()) {
                printf("next %d", item->next_state);
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
    for (Item item : state->GetItems()) {
        if (!item->IsDotEnd()) {
            Symbol token      = item->GetTokenAfterDot();
            tokens[token->id] = token;
        }
    }

    for (auto iter = tokens.begin(); iter != tokens.end(); iter++) {
        Symbol token = iter->second;

        ItemList movedRules;
        ItemList newStateRules;
        for (Item item : state->GetItems()) {
            if (!item->IsDotEnd() && ItemRight(item, item->dot)->id == token->id) {
                movedRules.push_back(item);

                Item n = item->Clone();
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
            for (Item newItem : newStateRules) {
                _stateList->GetState(_maxState)->Add(newItem);
            };
        } else {
            // 找到了
            for (Item item : movedRules) {
                item->next_state = sameState->GetId();
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
                    if (c->rule->left == r->rule->left && SymbolListEqual(c->rule->right, r->rule->right)) {
                        for (int token : r->GetTokens()) {
                            _actionTable->AddRule(stateId, token, ruleId, r->rule->root);
                        }
                    }
                }
            } else {
                Symbol token = ItemRight(r, r->dot);
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
                auto rule_left_id_eq = [word](Item rule) -> bool { return ItemLeft(rule) == word->id; };
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
            return r->dot == rule->dot && ItemLeft(r) == ItemLeft(rule)
                   && SymbolListEqual(ItemRights(r), ItemRights(rule));
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
SemaParser::searchSameState(const ItemList& newStateItems) {
    int max{ _stateList->Size() };
    for (int i{ 0 }; i < max; i++) {
        State state = _stateList->GetState(i);
        if (state->MatchItem(newStateItems)) {
            return state;
        }
    }
    return nullptr;
}

std::string
join(const SymbolList& v) {
    std::string a;
    for (Symbol t : v) {
        a += t->name;
        a += ",";
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
    size_t pos;
    // handle $$, $n
    std::string tmp = rule->rule->funcBlock;
    for (size_t i = ItemRightSize(rule), e = 0; i != e; i--) {
        std::string name = this->_typeMap[ItemRight(rule, i - 1)->name];
        std::string w    = "$" + std::to_string(i - 1);
        std::string r    = "(child[" + std::to_string(i - 1);
        r += "].";
        r += name;
        r += ")";
        while ((pos = tmp.find(w)) != std::string::npos)
            tmp.replace(pos, w.size(), r);
    }

    std::string name = Symtab::GetName(ItemLeft(rule));

    while ((pos = tmp.find("$$")) != std::string::npos) {
        name = "(item." + this->_typeMap[name] + ")";
        tmp.replace(pos, 2, name);
    }
    // handle @@, @n
    for (size_t i = ItemRightSize(rule), e = 0; i != e; i--) {
        std::string name = this->_typeMap[ItemRight(rule, i - 1)->name];
        std::string w    = "@" + std::to_string(i - 1);
        std::string r    = "(child[" + std::to_string(i - 1);
        r += "]";
        while ((pos = tmp.find(w)) != std::string::npos)
            tmp.replace(pos, w.size(), r);
    }

    name = Symtab::GetName(ItemLeft(rule));

    while ((pos = tmp.find("@@")) != std::string::npos) {
        name = "(item)";
        tmp.replace(pos, 2, name);
    }
    return tmp;
}
