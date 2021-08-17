#include "output.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

static FILE* readFile(const char* file);
static void writeFile(FILE* f, const char* buf);
static void closeFile(FILE* f);

Output::Output(Parser* _p)
    : parser { _p } {
}

void
Output::output(const char* filename) {
    FILE* fd = readFile(filename);
    // lex part
    writeFile(fd, "#ifndef _p_test_hpp_\n");
    writeFile(fd, "#define _p_test_hpp_\n");
    writeFile(fd, "#include <iostream>\n");
    writeFile(fd, "#include <stack>\n");
    writeFile(fd, "#include <vector>\n");
    writeFile(fd, "#include \"gogo.hpp\"\n");
    writeFile(fd, "#include \"TokenKinds.hpp\"\n");
    writeFile(fd, "#include \"sema.hpp\"\n");
    writeFile(fd, "using namespace std;\n");
    writeFile(fd, "\n");
    writeFile(fd, "\n");
    writeFile(fd, "union Item {Node node;std::vector<Node>* list;};\n");
    {
        char* a = new char[256];
        sprintf(a, "#define MAX_ID 65535\n");

        writeFile(fd, a);
        delete[] a;
    }
    // init goto table
    writeFile(fd, "// init goto table (state id, sema id) -> (state id)\n");
    {
        char* a = new char[256];
        sprintf(a, "const int goto_table[%d][%d]={\n", parser->_stateList->Size(), parser->_maxState);
        writeFile(fd, a);
        delete[] a;
        // init data
        for (int i{ 0 }; i < parser->_stateList->Size(); i++) {
            writeFile(fd, "{");
            for (int j{ 0 }; j < parser->_maxState; j++) {
                Record record = parser->_gotoTable->Find(i, j);
                if (record != nullptr) {
                    char* a1 = new char[256];
                    sprintf(a1, "%d,", record->id);
                    writeFile(fd, a1);
                    delete[] a1;
                } else {
                    writeFile(fd, "MAX_ID,");
                }
            }
            writeFile(fd, "},\n");
        }
        writeFile(fd, "};\n");
    }

    // init action table
    // init goto table
    writeFile(fd, "// init action table (state id, token id) -> (acc, state, id)\n");
    {
        char* a = new char[256];
        sprintf(a, "const int action_table[%d][%d]={\n", parser->_stateList->Size(), Tok::NUM_TOKENS);
        writeFile(fd, a);
        delete[] a;
        // init data
        for (int i{ 0 }; i < parser->_stateList->Size(); i++) {
            writeFile(fd, "{");
            for (int j{ 0 }; j < Tok::NUM_TOKENS; j++) {
                Record record = parser->_actionTable->Find(i, j);
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
                    writeFile(fd, a1);
                    delete[] a1;
                } else {
                    writeFile(fd, "MAX_ID,");
                }
            }
            writeFile(fd, "},\n");
        }
        writeFile(fd, "};\n");
    }
    // init rule right child size array
    writeFile(fd, "const int rule_right_children_num_arr[] = {");
    for (int rId{ 0 }; rId < parser->_rules.size(); rId++) {
        char* a = new char[256];
        sprintf(a, "%zd,", parser->_rules[rId]->right.size());

        writeFile(fd, a);
        delete[] a;
    }
    writeFile(fd, "};\n");
    // init rule left id array
    writeFile(fd, "const int rule_left_id_arr[] = {");
    for (int rId{ 0 }; rId < parser->_rules.size(); rId++) {
        char* a = new char[256];
        sprintf(a, "%d,", parser->_rules[rId]->left->id);

        writeFile(fd, a);
        delete[] a;
    }
    writeFile(fd, "};\n");

    writeFile(fd, "static bool eatToken(std::stack<int>& states, std::stack<Item>& syms, std::stack<LexToken>& input, bool* "
           "acc);\n");
    writeFile(fd, "static bool reduce(std::stack<int>& states, std::stack<Item>& syms, int r_id);\n");
    writeFile(fd, "Node raw_parse(const char* str);\n");
    writeFile(fd, "\n");

    writeFile(fd, "Node\nraw_parse(const char* str){\n");

    writeFile(fd, "  Lexer lexer(str, strlen(str));\n");
    writeFile(fd, "  LexToken t;\n");
    writeFile(fd, "  std::vector<LexToken> data;\n");
    writeFile(fd, "  while ((t = lexer.GetLexerToken()) != nullptr) {\n");
    writeFile(fd, "    if (t->tok != Tok::whitespace) {\n");
    writeFile(fd, "      data.push_back(t);\n");
    writeFile(fd, "    }\n");
    writeFile(fd, "  }\n");
    writeFile(fd, "  data.push_back(EndLexToken);\n");
    writeFile(fd, "\n");
    // sema part
    writeFile(fd, "  Item item;\n");
    writeFile(fd, "  std::stack<int> state_stack;\n");
    writeFile(fd, "  std::stack<Item> token_stack;\n");
    writeFile(fd, "  std::stack<LexToken> input_stack;\n");
    writeFile(fd, " \n");
    writeFile(fd, "  state_stack.push(0);\n");
    writeFile(fd, " \n");
    writeFile(fd, "  for (auto iter = data.rbegin(); iter != data.rend(); iter++) {\n");
    writeFile(fd, "    input_stack.push(*iter);\n");
    writeFile(fd, "  }\n");
    writeFile(fd, " \n");
    writeFile(fd, " bool acc{};\n");
    writeFile(fd, "  while (!acc) {\n");
    writeFile(fd, "    bool op = eatToken(state_stack, token_stack, input_stack, &acc);\n");
    writeFile(fd, " \n");
    writeFile(fd, "    if (!op) {\n");
    writeFile(fd, "      std::cout << \" no action \" << std::endl;\n");
    writeFile(fd, "      break;\n");
    writeFile(fd, "    }\n");
    writeFile(fd, "  }\n");
    writeFile(fd, "  if (acc) {\n");
    writeFile(fd, "    item = token_stack.top();\n");
    writeFile(fd, "  } else {\n");
    writeFile(fd, "    while (!token_stack.empty()) {\n");
    writeFile(fd, "      item = token_stack.top();\n");
    writeFile(fd, "      token_stack.pop();\n");
    writeFile(fd, "      delete item.node;\n");
    writeFile(fd, "    }\n");
    writeFile(fd, "  }\n");
    writeFile(fd, "  return item.node;\n");
    writeFile(fd, "}\n");

    // eattoken

    writeFile(fd, "bool\neatToken(std::stack<int> & states, std::stack<Item> & syms, std::stack<LexToken> & input, bool* acc) "
           "{\n");
    writeFile(fd, "  int curStateId = states.top();\n");
    writeFile(fd, "  LexToken token = input.top();\n");
    writeFile(fd, "  bool r_acc;\n");
    writeFile(fd, "  bool r_state;\n");
    writeFile(fd, "  int r_id;\n");
    writeFile(fd, "  bool r_find{false};\n");

    writeFile(fd, "  int rd = action_table[curStateId][token->tok];\n");
    writeFile(fd, "  r_acc = ( rd == 10000 );\n");
    writeFile(fd, "  r_state = ( rd > 0 );\n");
    writeFile(fd, "  r_id = rd > 0 ? rd : -rd;\n");
    writeFile(fd, "  r_find = ( r_id != MAX_ID );\n");

    writeFile(fd, "  if (r_find == true) {\n");
    writeFile(fd, "\n");
    writeFile(fd, "    if (r_acc == true) {\n");
    writeFile(fd, "      *acc = true;\n");
    writeFile(fd, "      return true;\n");
    writeFile(fd, "    }\n");
    writeFile(fd, "\n");
    writeFile(fd, "    if (r_state == true) {\n");
    writeFile(fd, "      states.push(r_id);\n");
    writeFile(fd, "      Item it;\n");
    writeFile(fd, "      it.node = new NodeData(token);\n");
    writeFile(fd, "      syms.push(it);\n");
    writeFile(fd, "      input.pop();\n");
    writeFile(fd, "      return true;\n");
    writeFile(fd, "    } else {\n");
    writeFile(fd, "      return reduce(states, syms, r_id);\n");
    writeFile(fd, "    }\n");
    writeFile(fd, "  }\n");
    writeFile(fd, "  return false;\n");
    writeFile(fd, "}\n ");

    // reduce

    writeFile(fd, "bool\nreduce(std::stack<int> & states, std::stack<Item> & syms, int r_id) {\n");
    writeFile(fd, "    int child_num{rule_right_children_num_arr[r_id]};\n");
    writeFile(fd, "    int rule_left_id{rule_left_id_arr[r_id]};\n");
    writeFile(fd, "    std::vector<Item> child(child_num);\n");
    writeFile(fd, "    Item item = syms.top();\n");

    writeFile(fd, "      for (int i{ 0 }; i < child_num; i++) {\n");
    writeFile(fd, "        child.insert(child.begin(), syms.top());\n");
    writeFile(fd, "        syms.pop();\n");
    writeFile(fd, "        states.pop();\n");
    writeFile(fd, "      }\n");

    writeFile(fd, "    switch(r_id) {\n");
    for (int i1{ 0 }; i1 < parser->_rules.size(); i1++) {
        char* a = new char[256];
        sprintf(a, "    case %d:  \n", i1);
        writeFile(fd, a);
        writeFile(fd, "\n");
        // 写line comment
        memset(a, 0, 256);
        sprintf(a, "// line %d\n", parser->_originRules[i1]->lineId);
        writeFile(fd, a); // 写 {} 块
        memset(a, 0, 256);
        std::string g = parser->funcReplace(parser->_rules[i1]);
        sprintf(a, "//block\n      {\n %s \n      }\n", g.c_str());
        writeFile(fd, a);

        writeFile(fd, "      break;\n");

        delete[] a;
    }
    writeFile(fd, "    }");
    writeFile(fd, "    syms.push(item);\n");

    writeFile(fd, "\n");
    writeFile(fd, "    int curStateId = states.top();\n");
    writeFile(fd, "    int nextStateId = goto_table[curStateId][rule_left_id];\n");
    writeFile(fd, "    states.push(nextStateId);\n");
    writeFile(fd, "    return true;\n");
    writeFile(fd, "}\n");
    writeFile(fd, "#endif\n");

    closeFile(fd);
};


FILE*
readFile(const char* file) {
    FILE* f = fopen(file, "w");
    return f;
}

void
writeFile(FILE* f, const char* buf) {
    int len = strlen(buf);
    fprintf(f, buf);
}

void
closeFile(FILE* f) {
    fclose(f);
}
