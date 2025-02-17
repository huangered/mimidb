#include "sema.hpp"
#include <string>
#include <functional>
#include <cstring>
#include "debug.hpp"
#include "symtab.hpp"
#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
#include <stack>
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

SemaParser::SemaParser(const std::map<std::string, std::string>& typeMap)
    : _maxState{ 0 }
    , _typeMap{ typeMap } {
    _firstSet  = std::unique_ptr<FirstSet>(new FirstSet());
    _stateList = std::unique_ptr<StateCollection>(new StateCollection());
    _stateList->Add(new StateData{ 0 });

    Item rootRule;

    for (Rule rule : Rules) {
        if (ItemRoot(rule)) {
            rootRule     = new ItemData{};
            rootRule->id = rule->id;

            rootRule->SetToken(Symtab::eof->id);
            break;
        }
    }

    _stateList->Add(0, rootRule);
}

SemaParser::~SemaParser() {
}

void
SemaParser::GenerateParseTable(void) {
    _firstSet->Gen();
    _firstSet->Print();
    printf("----------%d\n", _stateList->Size());

    std::set<State> state_set;
    std::stack<State> state_stack;

    state_set.insert(_stateList->GetState(0));
    state_stack.push(_stateList->GetState(0));

    while (!state_stack.empty()) {
        State top = state_stack.top();
        state_stack.pop();

        std::vector<State> rets = handleState(top);
        for (State s : rets) {
            if (state_set.count(s) == 0) {
                state_set.insert(s);
                state_stack.push(s);
            }
        }
    }
    printf("**********debug\n");
    for (int i{}; i < _stateList->Size(); i++) {
        State s = _stateList->GetState(i);
        s->print();
    }

#ifdef abc
    printf("state list:\n");
    for (int i{}; i < _stateList->Size(); i++) {
        if (_stateList->IsEmpty(i)) {
            break;
        }
        printf("state %d:\n", i);
        for (Item item : _stateList->GetRules(i)) {
            auto r_str = join(ItemRights(item));
            auto t_str = join2(item->tokens);
            printf("     %s => %s [ %s ] (%d) ", ItemLeft(item)->name.c_str(), r_str.c_str(), t_str.c_str(), item->dot);

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
std::vector<State>
SemaParser::handleState(State state) {
    std::vector<State> rets;
    printf("Handle state %d\n", state->GetId());
    // 1. 扩展规则
    rets = expandRules(state);
    // 2. 构建新状态
    return rets;
}

void
SemaParser::generateTable(void) {
    _gotoTable   = std::unique_ptr<GotoTable>(new GotoTable(_stateList->Size(), Symtab::nsym - Symtab::ntoken()));
    _actionTable = std::unique_ptr<ActionTable>(new ActionTable(_stateList->Size(), Symtab::ntoken()));

    for (int stateId{0}; stateId < _stateList->Size(); stateId++) {
        for (Item r : _stateList->GetState(stateId)->_closures) {
            if (r->IsDotEnd()) {
                // find rule id
                // add r1 in action
                _actionTable->AddRule(stateId, token, r->id, ItemRoot(r));
                /*
                for (int ruleId{}; ruleId < Rules.size(); ruleId++) {
                    Rule c = Rules[ruleId];
                    if (c->left == Rules[r->id]->left && SymbolListEqual(c->right, Rules[r->id]->right)) {
                        for (int token : r->GetTokens()) {
                            _actionTable->AddRule(stateId, token, ruleId, ItemRoot(r));
                        }
                    }
                }*/
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

struct ItemLess {
    bool
    operator()(const Item l, const Item r) const {
        if (l->id == r->id) {
            return l->dot < r->dot;
        }
        return l->id < r->id;
    }
};

// 创建closure items
std::vector<State>
SemaParser::expandRules(State state) {
    state->print();
    std::vector<State> rets;

    std::stack<Item> item_stack;
    std::set<Item, ItemLess> item_set;

    // init
    for (Item item : state->_items) {
        Item copy        = item->Clone();
        copy->next_state = 0;
        item_stack.push(copy);
        item_set.insert(copy);
    }

    while (!item_stack.empty()) {
        Item top = item_stack.top();
        item_stack.pop();

        if (top->IsDotEnd()) {
            continue;
        }

        Symbol word = top->GetTokenAfterDot();
        if (word->clazz == nterm) {
            // 非终止符，查询rule进行替换
            auto rule_left_id_eq = [word](Rule rule) -> bool { return ItemLeft(rule)->id == word->id; };
            RuleList match;
            find_all(Rules, match, rule_left_id_eq);
            for (Rule rule : match) {
                SymbolList tokenList    = top->GetStringAfterDot();
                std::vector<int> tokens = _firstSet->Find(tokenList, top->GetTokens());
                // todo: 这里可以优化这个lazy clone
                Item copy = new ItemData{};
                copy->id  = rule->id;
                copy->dot = 0;
                copy->SetTokens(tokens);
                // 如果是新rule
                if (item_set.find(copy) != item_set.end()) {
                    // 有
                    delete copy;
                    continue;
                } else {
                    item_stack.push(copy);
                    item_set.insert(copy);
                }
            }
        }
    }
    // update closure
    for (Item i : item_set) {
        state->_closures.push_back(i);
    }

    // 合并 state 里的 rules
    std::map<int, ItemList> group_map;
    for (Item rule : item_set) {
        if (rule->IsDotEnd()) {
            // this is end;
            // set to reduce;
            continue;
        }
        Symbol token = rule->GetTokenAfterDot();
        if (group_map.count(token->id) == 0) {
            ItemList l = { rule };
            group_map.insert(std::make_pair(token->id, l));
        } else {
            group_map[token->id].push_back(rule);
        }
    }

    for (auto i : group_map) {
        int k      = i.first;
        ItemList v = i.second;
        ItemList copylist;
        for (Item i : v) {
            if (!i->IsDotEnd()) {
                Item copy = i->Clone();
                copy->dot++;
                copylist.push_back(copy);
            }
        }
        State s = this->_stateList->has(copylist);
        if (s != nullptr) {
            // 找到了重复state
            std::for_each(v.begin(), v.end(), [s](Item i) { i->next_state = s->_id; });
        } else {
            // 没找到 state
            State new_state = new StateData(this->_stateList->GetNextId());

            std::for_each(v.begin(), v.end(), [new_state](Item i) { i->next_state = new_state->_id; });

            new_state->ResetItems(copylist);

            rets.push_back(new_state);

            //
            this->_stateList->Add(new_state);
        }
    }

    return rets;
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
    std::string a = format_string<int>(v);
    return a;
}

std::string
SemaParser::funcReplace(const Rule rule) {
    size_t pos;
    // handle $$, $n
    std::string tmp = rule->funcBlock;
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

    std::string name = ItemLeft(rule)->name;

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

    name = ItemLeft(rule)->name;

    while ((pos = tmp.find("@@")) != std::string::npos) {
        name = "(item)";
        tmp.replace(pos, 2, name);
    }
    return tmp;
}
