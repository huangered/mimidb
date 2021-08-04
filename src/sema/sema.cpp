#include "sema/sema.hpp"
#include <string>
#include <functional>
extern "C" {
#include "storage/fd.h"
}
#include <cstring>

static bool SemaTokenListLess(const SemaTokenList& left, const SemaTokenList& right);
static std::string join(const SemaTokenList& v);
static std::string join2(const std::vector<Tok>& v);
static std::string funcReplace(std::string fblock, int size);

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

bool
group_key::operator<(const group_key& g1) const {
    int i{ 0 };

    if ((i = dot - g1.dot) != 0) {
        return i < 0 ? true : false;
    }
    if ((i = left->id - g1.left->id) != 0) {
        return i < 0 ? true : false;
    }

    return SemaTokenListLess(right, g1.right);
}

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

Parser::Parser(const std::vector<SimpleRule>& rules)
    : _maxState{ 0 }
    , _firstSet{ std::make_unique<FirstSet>(rules) }
    , _stateList{ std::make_unique<StateCollection>() } {
    _originRules.insert(_originRules.begin(), rules.begin(), rules.end());
    _stateList->Add(new StateData{ 0 });

    for (SimpleRule rule : rules) {
        Rule r        = new RuleData{};
        r->id         = rule->id;
        r->left       = rule->left;
        r->right      = rule->right;
        r->func_block = rule->funcBlock;
        _rules.push_back(r);
    }
    _rules[0]->root = true;

    Rule rule = _rules[0]->Clone();
    rule->SetToken(Tok::Eof);
    _stateList->Add(0, rule);
}

Parser::~Parser() {
    for (Rule r : _rules) {
        delete r;
    }
}

void
Parser::GenerateParseTable(void) {
    _firstSet->Gen();
    // _firstSet->Print();
    for (int i{}; i < _stateList->Size(); i++) {
        if (_stateList->IsEmpty(i)) {
            break;
        }

        handleState(i);
    }
    /*
    for (int i{}; i < _stateList->Size(); i++) {
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
    */
    generateTable();
}

std::pair<bool, Node>
Parser::Parse(const std::vector<LexToken>& input) {
    bool acc{ false };
    Node node{ nullptr };
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
    if (acc) {
        node = token_stack.top();
    } else {
        while (!token_stack.empty()) {
            node = token_stack.top();
            token_stack.pop();
            delete node;
            node = nullptr;
        }
    }

    return std::make_pair(acc, node);
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
            SemaToken token   = rule->GetTokenAfterDot();
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
t1(File fd, char* buf) {
    int size = strlen(buf);
    FileWrite(fd, buf, size);
}

void
Parser::GenerateCppCode(const char* path) {
    File fd = PathNameOpenFile(path);

    // char* buf = new char[256];
    // lex part
    t1(fd, "#ifndef _p_test_hpp_\n");
    t1(fd, "#define _p_test_hpp_\n");
    t1(fd, "#include <iostream>\n");
    t1(fd, "#include <stack>\n");
    t1(fd, "#include <vector>\n");
    t1(fd, "#include \"sema/gogo.hpp\"\n");
    t1(fd, "#include \"lex/TokenKinds.hpp\"\n");
    t1(fd, "#include \"sema/sema.hpp\"\n");
    t1(fd, "using namespace std;\n");
    t1(fd, "union Item {Node node;};\n");
    t1(fd, "\n");

    {
        char* a = new char[256];
        sprintf(a, "#define MAX_ID 65535\n");

        t1(fd, a);
        delete[] a;
    }
    // init goto table
    t1(fd, "// init goto table (state id, sema id) -> (state id)\n");
    {
        char* a = new char[256];
        sprintf(a, "const int goto_table[%d][%d]={\n", _stateList->Size(), _maxState);
        t1(fd, a);
        delete[] a;
        // init data
        for (int i{ 0 }; i < _stateList->Size(); i++) {
            t1(fd, "{");
            for (int j{ 0 }; j < _maxState; j++) {
                Record record = _gotoTable->Find(i, j);
                if (record != nullptr) {
                    char* a1 = new char[256];
                    sprintf(a1, "%d,", record->id);
                    t1(fd, a1);
                    delete[] a1;
                } else {
                    t1(fd, "MAX_ID,");
                }
            }
            t1(fd, "},\n");
        }
        t1(fd, "};\n");
    }

    // init action table
    // init goto table
    t1(fd, "// init action table (state id, token id) -> (acc, state, id)\n");
    {
        char* a = new char[256];
        sprintf(a, "const int action_table[%d][%d]={\n", _stateList->Size(), Tok::NUM_TOKENS);
        t1(fd, a);
        delete[] a;
        // init data
        for (int i{ 0 }; i < _stateList->Size(); i++) {
            t1(fd, "{");
            for (int j{ 0 }; j < Tok::NUM_TOKENS; j++) {
                Record record = _actionTable->Find(i, j);
                if (record != nullptr) {

                    std::string str = "";
                    if (record->acc) {
                        str += "10000";
                    } else if (record->state) {
                        str += std::to_string(record->id);
                    } else {
                        str += "-";
                        str += std::to_string(record->id);
                    }
                    char* a1 = new char[1024];
                    sprintf(a1, "%s,", str.c_str());
                    t1(fd, a1);
                    delete[] a1;
                } else {
                    t1(fd, "MAX_ID,");
                }
            }
            t1(fd, "},\n");
        }
        t1(fd, "};\n");
    }
    // init rule right child size array
    t1(fd, "const int rule_right_children_num_arr[] = {");
    for (int rId{ 0 }; rId < _rules.size(); rId++) {
        char* a = new char[256];
        sprintf(a, "%zd,", _rules[rId]->right.size());

        t1(fd, a);
        delete[] a;
    }
    t1(fd, "};\n");
    // init rule left id array
    t1(fd, "const int rule_left_id_arr[] = {");
    for (int rId{ 0 }; rId < _rules.size(); rId++) {
        char* a = new char[256];
        sprintf(a, "%d,", _rules[rId]->left->id);

        t1(fd, a);
        delete[] a;
    }
    t1(fd, "};\n");

    t1(fd, "static bool eatToken(std::stack<int>& states, std::stack<Item>& syms, std::stack<LexToken>& input, bool* "
           "acc);\n");
    t1(fd, "static bool reduce(std::stack<int>& states, std::stack<Item>& syms, int r_id);\n");
    t1(fd, "Node raw_parse(const char* str);\n");
    t1(fd, "\n");

    t1(fd, "Node\nraw_parse(const char* str){\n");

    t1(fd, "  Lexer lexer(str, strlen(str));\n");
    t1(fd, "  LexToken t;\n");
    t1(fd, "  std::vector<LexToken> data;\n");
    t1(fd, "  while ((t = lexer.GetLexerToken()) != nullptr) {\n");
    t1(fd, "    if (t->tok != Tok::whitespace) {\n");
    t1(fd, "      data.push_back(t);\n");
    t1(fd, "    }\n");
    t1(fd, "  }\n");
    t1(fd, "  data.push_back(EndLexToken);\n");
    t1(fd, "\n");
    // sema part
    t1(fd, "  Item item{ nullptr };\n");
    t1(fd, "  std::stack<int> state_stack;\n");
    t1(fd, "  std::stack<Item> token_stack;\n");
    t1(fd, "  std::stack<LexToken> input_stack;\n");
    t1(fd, " \n");
    t1(fd, "  state_stack.push(0);\n");
    t1(fd, " \n");
    t1(fd, "  for (auto iter = data.rbegin(); iter != data.rend(); iter++) {\n");
    t1(fd, "    input_stack.push(*iter);\n");
    t1(fd, "  }\n");
    t1(fd, " \n");
    t1(fd, " bool acc{};\n");
    t1(fd, "  while (!acc) {\n");
    t1(fd, "    bool op = eatToken(state_stack, token_stack, input_stack, &acc);\n");
    t1(fd, " \n");
    t1(fd, "    if (!op) {\n");
    t1(fd, "      std::cout << \" no action \" << std::endl;\n");
    t1(fd, "      break;\n");
    t1(fd, "    }\n");
    t1(fd, "  }\n");
    t1(fd, "  if (acc) {\n");
    t1(fd, "    item = token_stack.top();\n");
    t1(fd, "  } else {\n");
    t1(fd, "    while (!token_stack.empty()) {\n");
    t1(fd, "      item = token_stack.top();\n");
    t1(fd, "      token_stack.pop();\n");
    t1(fd, "      delete item.node;\n");
    t1(fd, "    }\n");
    t1(fd, "  }\n");
    t1(fd, "  return item.node;\n");
    t1(fd, "}\n");

    // eattoken

    t1(fd, "bool\neatToken(std::stack<int> & states, std::stack<Item> & syms, std::stack<LexToken> & input, bool* acc) "
           "{\n");
    t1(fd, "  int curStateId = states.top();\n");
    t1(fd, "  LexToken token = input.top();\n");
    t1(fd, "  bool r_acc;\n");
    t1(fd, "  bool r_state;\n");
    t1(fd, "  int r_id;\n");
    t1(fd, "  bool r_find{false};\n");

    t1(fd, "  int rd = action_table[curStateId][token->tok];\n");
    t1(fd, "  r_acc = (rd==10000);\n");
    t1(fd, "  r_state = (rd>0);\n");
    t1(fd, "  r_id = rd>0?rd:-rd;\n");
    t1(fd, "  r_find = (r_id!=MAX_ID);\n");

    t1(fd, "  if (r_find == true) {\n");
    t1(fd, "\n");
    t1(fd, "    if (r_acc == true) {\n");
    t1(fd, "      *acc = true;\n");
    t1(fd, "      return true;\n");
    t1(fd, "    }\n");
    t1(fd, "\n");
    t1(fd, "    if (r_state == true) {\n");
    t1(fd, "      states.push(r_id);\n");
    t1(fd, "      syms.push(Item{new NodeData(token)});\n");
    t1(fd, "      input.pop();\n");
    t1(fd, "      return true;\n");
    t1(fd, "    } else {\n");
    t1(fd, "      return reduce(states, syms, r_id);\n");
    t1(fd, "    }\n");
    t1(fd, "  }\n");
    t1(fd, "  return false;\n");
    t1(fd, "}\n ");

    // reduce

    t1(fd, "bool\nreduce(std::stack<int> & states, std::stack<Item> & syms, int r_id) {\n");
    t1(fd, "    int child_num{rule_right_children_num_arr[r_id]};\n");
    t1(fd, "    int rule_left_id{rule_left_id_arr[r_id]};\n");
    t1(fd, "    std::vector<Item> child;\n");
    t1(fd, "    Item item{ nullptr};\n");

    t1(fd, "      for (int i{ 0 }; i < child_num; i++) {\n");
    t1(fd, "        child.push_back(syms.top());\n");
    t1(fd, "        syms.pop();\n");
    t1(fd, "        states.pop();\n");
    t1(fd, "      }\n");

    t1(fd, "    switch(r_id) {");
    for (int i1{ 0 }; i1 < _rules.size(); i1++) {
        char* a = new char[256];
        sprintf(a, "    case %d:  \n", i1);
        t1(fd, a);
        t1(fd, "\n");
        // 写line comment
        memset(a, 0, 256);
        sprintf(a, "// line %d\n", _originRules[i1]->lineId);
        t1(fd, a); // 写 {} 块
        memset(a, 0, 256);
        std::string g = funcReplace(_rules[i1]->func_block, _rules[i1]->right.size());
        sprintf(a, "//block\n      { %s }\n", g.c_str());
        t1(fd, a);

        t1(fd, "      break;\n");

        delete[] a;
    }
    t1(fd, "    }");
    t1(fd, "    syms.push(item);\n");

    t1(fd, "\n");
    t1(fd, "    int curStateId = states.top();\n");
    t1(fd, "    int nextStateId{0};\n");
    t1(fd, "    nextStateId = goto_table[curStateId][rule_left_id];\n");
    t1(fd, "    states.push(nextStateId);\n");
    t1(fd, "    return true;\n");
    t1(fd, "}\n");
    t1(fd, "#endif\n");

    FileClose(fd);
}

void
Parser::generateTable(void) {
    _gotoTable   = std::make_unique<GotoTable>(_stateList->Size(), _maxState);
    _actionTable = std::make_unique<ActionTable>(_stateList->Size(), Tok::NUM_TOKENS);

    for (int stateId{}; stateId < _stateList->Size(); stateId++) {
        for (Rule r : _stateList->GetRules(stateId)) {
            if (r->IsDotEnd()) {
                // find rule id
                // add r1 in action
                for (int ruleId{}; ruleId < _rules.size(); ruleId++) {
                    Rule c = _rules[ruleId];
                    if (c->left->id == r->left->id && SemaTokenListEqual(c->right, r->right)) {
                        for (Tok token : r->GetTokens()) {
                            _actionTable->AddRule(stateId, token, ruleId, r->root);
                        }
                    }
                }
            } else {
                SemaToken token = r->right[r->dot];
                if (token->sema) {
                    // update goto
                    _gotoTable->Add(stateId, token->id, r->next_state);
                } else {
                    // update action
                    _actionTable->Add(stateId, GetTokByName(token->name), r->next_state);
                }
            }
        }
    }
    //_actionTable->Print();
    //_gotoTable->Print();
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
                    SemaTokenList tokenList = r->GetStringAfterDot();
                    TokList tokens          = _firstSet->Find(tokenList, r->GetTokens());
                    // todo: 这里可以优化这个lazy clone
                    Rule copy = rule->Clone();
                    copy->dot = 0;
                    copy->SetTokens(tokens);
                    // 如果是新rule
                    auto rule_eq = [copy](Rule rule) -> bool { return *rule == *copy; };
                    RuleList src = state->GetRules();
                    RuleList dest;
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

    RuleList tmp;
    std::multimap<group_key, Rule, std::less<group_key>> gg;

    // 合并 state 里的 rules
    for (Rule rule : state->GetRules()) {
        auto check_exist = [rule](Rule r) -> bool {
            return r->dot == rule->dot && r->left->id == rule->left->id && SemaTokenListEqual(r->right, rule->right);
        };

        auto iter = std::find_if(tmp.begin(), tmp.end(), check_exist);
        if (iter != tmp.end()) {
            Rule r = *iter;
            r->AppendTokens(rule->tokens);
        } else {
            tmp.push_back(rule->Clone());
        }
    }
    state->ResetRules(tmp);
    std::for_each(tmp.begin(), tmp.end(), [](Rule r) { delete r; });
}

State
Parser::searchSameState(const RuleList& newStateRules) {
    int max{ _stateList->Size() };
    for (int i{ 0 }; i < max; i++) {
        State state = _stateList->GetState(i);
        if (state->MatchRule(newStateRules)) {
            return state;
        }
    }
    return nullptr;
}

/*
 *使用规则
 */
bool
Parser::reduce(std::stack<int>& states, std::stack<Node>& syms, const Record record) {
    if (!record->state) {
        Rule rule = _rules[record->id];
        std::vector<Node> child;
        for (int i{ 0 }; i < rule->right.size(); i++) {
            child.push_back(syms.top());
            syms.pop();
            states.pop();
        }

        Node node = rule->Format(rule->left, child);
        syms.push(node);

        // find goto table
        int curStateId = states.top();

        int nextStateId = _gotoTable->Find(curStateId, rule->left->id)->id;
        states.push(nextStateId);
        return true;
    }
    return false;
}

bool
Parser::eatToken(std::stack<int>& states, std::stack<Node>& syms, std::stack<LexToken>& input, bool* acc) {
    int curStateId = states.top();
    LexToken token = input.top();
    Record record  = _actionTable->Find(curStateId, token->tok);
    if (record != nullptr) {

        if (record->acc) {
            *acc = true;
            return true;
        }

        if (record->state) {
            states.push(record->id);
            syms.push(new NodeData(token));
            input.pop();
            return true;
        } else {
            return reduce(states, syms, record);
        }
    }
    return false;
}

std::string
join(const SemaTokenList& v) {
    std::string a;
    for (SemaToken t : v) {
        if (t->sema) {
            a += t->name;
            a += ",";
        } else {
            a += GetTokByName(t->name);
            a += ",";
        }
    }
    return a;
}

std::string
join2(const TokList& v) {
    std::string a;
    for (Tok t : v) {
        a += t;
        a += ",";
    }
    return a;
}

bool
SemaTokenListEqual(const SemaTokenList& left, const SemaTokenList& right) {
    if (left.size() != right.size()) {
        return false;
    }

    for (int i{ 0 }; i < left.size(); i++) {
        if (left[i]->id != right[i]->id) {
            return false;
        }
    }

    return true;
}

bool
SemaTokenListLess(const SemaTokenList& left, const SemaTokenList& right) {
    int i{ 0 };

    if ((i = left.size() - right.size()) != 0) {
        return i < 0 ? true : false;
    }

    for (int j{ 0 }; j < left.size(); j++) {
        if ((i = left[j]->id - right[j]->id) != 0) {
            return i < 0 ? true : false;
        }
    }

    return false;
}

std::string
funcReplace(std::string fblock, int size) {
    std::string tmp = fblock;
    for (int i{ 0 }; i < size; i++) {
        std::string w = "$" + std::to_string(i);
        std::string r = "child[" + std::to_string(i);
        r += "].node";
        std::size_t pos;
        while ((pos = tmp.find(w)) != std::string::npos)
            tmp.replace(pos, w.size(), r);
    }
    std::size_t pos;

    while ((pos = tmp.find("$$")) != std::string::npos)
        tmp.replace(pos, 2, "item.node");
    return tmp;
}