#include "output.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "reader.hpp"
#include "symtab.hpp"

Output::Output(Parser* _p)
    : parser{ _p } {
}

void
Output::SetCode(std::string b) {
    codeBlock = b;
}
void
Output::SetUnion(std::string b) {
    unionBlock = b;
}

void
Output::SetOther(std::string b) {
    other = b;
}

void
Output::SetParam(std::string p) {
    param = p;
}

void
Output::OutputFile(const char* filename) {
    writeHeaderFile();
    writerCppFile();
    writeM4();
};

FILE*
OpenFile(const char* file, const char* mode) {
    FILE* f = fopen(file, mode);
    assert(f);
    return f;
}

char*
ReadFile(FILE* f) {
    int r   = fseek(f, 0, SEEK_END);
    long sz = ftell(f);

    char* buf = new char[sz + 1];
    memset(buf, 0, sz + 1);
    fseek(f, 0, SEEK_SET);

    fread(buf, sizeof(char), sz, f);

    return buf;
}

void
WriteFile(FILE* f, const char* buf) {
    int len = strlen(buf);
    fprintf(f, "%s", buf);
}

void
CloseFile(FILE* f) {
    fclose(f);
}

void
Output::writeM4() {
  FILE* fd = OpenFile("value.m4", "w");

  writeCode(fd);

  writeUnion(fd);

  writeTokEnum(fd);
  
  CloseFile(fd);
}

void
Output::writeHeaderFile() {
    FILE* fd = OpenFile("c.tab.hpp", "w");

    WriteFile(fd, "#ifndef _c_tab_hpp_\n");
    WriteFile(fd, "#define _c_tab_hpp_\n");

    writeCode(fd);

    writeUnion(fd);

    writeTokEnum(fd);

    WriteFile(fd, "Node yyparse(const char* str);\n");

    writeOther(fd);

    WriteFile(fd, "#endif\n");

    CloseFile(fd);
}

void
Output::writerCppFile() {
    FILE* fd = OpenFile("c.tab.cpp", "w");

    WriteFile(fd, "#include \"c.tab.hpp\"\n");

    WriteFile(fd, "");

    WriteFile(fd, "union YYSTYPE yylval\n");

    WriteFile(fd, "struct InputToken{int tok;YYSTYPE item;};\n");

    {
        char* a = new char[256];
        sprintf(a, "#define MAX_ID 65535\n");

        WriteFile(fd, a);
        delete[] a;
    }
    // init goto table
    WriteFile(fd, "// init goto table (state id, sema id) -> (state id)\n");
    {
        char* a = new char[256];
        sprintf(a, "const int goto_table[%d][%d]={\n", parser->_stateList->Size(), Symtab::nsym - Symtab::ntoken());
        WriteFile(fd, a);
        delete[] a;
        // init data
        for (int i{ 0 }; i < parser->_stateList->Size(); i++) {
            WriteFile(fd, "{");
            for (int j{ 0 }; j < Symtab::nsym - Symtab::ntoken(); j++) {
                Record record = parser->_gotoTable->Find(i, j);
                if (record != nullptr) {
                    char* a1 = new char[256];
                    sprintf(a1, "%d,", record->id);
                    WriteFile(fd, a1);
                    delete[] a1;
                } else {
                    WriteFile(fd, "MAX_ID,");
                }
            }
            WriteFile(fd, "},\n");
        }
        WriteFile(fd, "};\n");
    }

    // init action table
    // init goto table
    WriteFile(fd, "// init action table (state id, token id) -> (acc, state, id)\n");
    {
        char* a = new char[256];
        sprintf(a, "const int action_table[%d][%d]={\n", parser->_stateList->Size(), Symtab::ntoken());
        WriteFile(fd, a);
        delete[] a;
        // init data
        for (int i{ 0 }; i < parser->_stateList->Size(); i++) {
            WriteFile(fd, "{");
            for (int j{ 0 }; j < Symtab::ntoken(); j++) {
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
                    WriteFile(fd, a1);
                    delete[] a1;
                } else {
                    WriteFile(fd, "MAX_ID,");
                }
            }
            WriteFile(fd, "},\n");
        }
        WriteFile(fd, "};\n");
    }
    // init rule right child size array
    WriteFile(fd, "const int rule_right_children_num_arr[] = {");
    for (int rId{ 0 }; rId < parser->_rules.size(); rId++) {
        char* a = new char[256];
        sprintf(a, "%zd,", parser->_rules[rId]->right.size());

        WriteFile(fd, a);
        delete[] a;
    }
    WriteFile(fd, "};\n");
    // init rule left id array
    WriteFile(fd, "const int rule_left_id_arr[] = {");
    for (int rId{ 0 }; rId < parser->_rules.size(); rId++) {
        char* a = new char[256];
        sprintf(a, "%d,", parser->_rules[rId]->left);

        WriteFile(fd, a);
        delete[] a;
    }
    WriteFile(fd, "};\n");

    WriteFile(
        fd,
        "static bool yyshift(std::stack<int>& states, std::stack<YYSTYPE>& syms, std::stack<InputToken*>& input, bool* "
        "acc);\n");
    WriteFile(fd, "static bool yyreduce(std::stack<int>& states, std::stack<YYSTYPE>& syms, int r_id);\n");

    WriteFile(fd, "\n");

    WriteFile(fd, "Node\nyyparse(const char* str){\n");

    WriteFile(fd, "  Lexer lexer(str, strlen(str));\n");
    WriteFile(fd, "  int t;\n");
    WriteFile(fd, "  std::vector<InputToken*> data;\n");
    WriteFile(fd, "  while ((t = lexer.Yylex()) != -1) {\n");
    WriteFile(fd, "     data.push_back(new InputToken{ t, yylval });\n");
    WriteFile(fd, "     memset(&yylval, 0 , sizeof(YYSTYPE));\n");
    WriteFile(fd, "  }\n");

    {
        char* a = new char[256];
        sprintf(a, "InputToken* end = new InputToken{};end->tok = %d;\n", Symtab::eof->id);

        WriteFile(fd, a);
        delete[] a;
    }
    WriteFile(fd, "  data.push_back(end);\n");
    WriteFile(fd, "\n");
    // sema part
    WriteFile(fd, "  YYSTYPE item{};\n");
    WriteFile(fd, "  std::stack<int> state_stack;\n");
    WriteFile(fd, "  std::stack<YYSTYPE> token_stack;\n");
    WriteFile(fd, "  std::stack<InputToken*> input_stack;\n");
    WriteFile(fd, " \n");
    WriteFile(fd, "  state_stack.push(0);\n");
    WriteFile(fd, " \n");
    WriteFile(fd, "  for (auto iter = data.rbegin(); iter != data.rend(); iter++) {\n");
    WriteFile(fd, "    input_stack.push(*iter);\n");
    WriteFile(fd, "  }\n");
    WriteFile(fd, " \n");
    WriteFile(fd, " bool acc{};\n");
    WriteFile(fd, "  while (!acc) {\n");
    WriteFile(fd, "    bool op = yyshift(state_stack, token_stack, input_stack, &acc);\n");
    WriteFile(fd, " \n");
    WriteFile(fd, "    if (!op) {\n");
    WriteFile(fd, "      std::cout << \" no action \" << std::endl;\n");
    WriteFile(fd, "      break;\n");
    WriteFile(fd, "    }\n");
    WriteFile(fd, "  }\n");
    WriteFile(fd, "  if (acc) {\n");
    WriteFile(fd, "    item = token_stack.top();\n");
    WriteFile(fd, "  } else {\n");
    WriteFile(fd, "    return nullptr;\n");
    WriteFile(fd, "    }\n");
    {
        char* a = new char[256];
        sprintf(a, "  %s* ptr = reinterpret_cast<%s*>(&item);\n", this->param.c_str(), this->param.c_str());
        WriteFile(fd, a);
        delete[] a;
    }

    WriteFile(fd, "  return *ptr;\n");
    WriteFile(fd, "}\n");

    // yyshift

    WriteFile(
        fd,
        "bool\nyyshift(std::stack<int> & states, std::stack<YYSTYPE> & syms, std::stack<InputToken*> & input, bool* acc) "
        "{\n");
    WriteFile(fd, "  int curStateId = states.top();\n");
    WriteFile(fd, "  LexToken token = input.top();\n");
    WriteFile(fd, "  bool r_acc;\n");
    WriteFile(fd, "  bool r_state;\n");
    WriteFile(fd, "  int r_id;\n");
    WriteFile(fd, "  bool r_find{false};\n");

    WriteFile(fd, "  int rd = action_table[curStateId][token->tok];\n");
    WriteFile(fd, "  r_acc = ( rd == 10000 );\n");
    WriteFile(fd, "  r_state = ( rd > 0 );\n");
    WriteFile(fd, "  r_id = rd > 0 ? rd : -rd;\n");
    WriteFile(fd, "  r_find = ( r_id != MAX_ID );\n");

    WriteFile(fd, "  if (r_find == true) {\n");
    WriteFile(fd, "\n");
    WriteFile(fd, "    if (r_acc == true) {\n");
    WriteFile(fd, "      *acc = true;\n");
    WriteFile(fd, "      return true;\n");
    WriteFile(fd, "    }\n");
    WriteFile(fd, "\n");
    WriteFile(fd, "    if (r_state == true) {\n");
    WriteFile(fd, "      states.push(r_id);\n");
    WriteFile(fd, "      YYSTYPE it = token->item;\n");
    WriteFile(fd, "      syms.push(it);\n");
    WriteFile(fd, "      input.pop();\n");
    WriteFile(fd, "      return true;\n");
    WriteFile(fd, "    } else {\n");
    WriteFile(fd, "      return yyreduce(states, syms, r_id);\n");
    WriteFile(fd, "    }\n");
    WriteFile(fd, "  }\n");
    WriteFile(fd, "  return false;\n");
    WriteFile(fd, "}\n ");

    // yyreduce

    WriteFile(fd, "bool\nyyreduce(std::stack<int> & states, std::stack<YYSTYPE> & syms, int r_id) {\n");
    WriteFile(fd, "    int child_num{rule_right_children_num_arr[r_id]};\n");
    WriteFile(fd, "    int rule_left_id{rule_left_id_arr[r_id]};\n");
    WriteFile(fd, "    std::vector<YYSTYPE> child(child_num);\n");
    WriteFile(fd, "    YYSTYPE item = syms.top();\n");

    WriteFile(fd, "      for (int i{ 0 }; i < child_num; i++) {\n");
    WriteFile(fd, "        child.insert(child.begin(), syms.top());\n");
    WriteFile(fd, "        syms.pop();\n");
    WriteFile(fd, "        states.pop();\n");
    WriteFile(fd, "      }\n");

    WriteFile(fd, "    switch(r_id) {\n");
    for (int i1{ 0 }; i1 < parser->_rules.size(); i1++) {
        char* a = new char[256];
        sprintf(a, "    case %d:  \n", i1);
        WriteFile(fd, a);
        WriteFile(fd, "\n");
        // 写line comment
        memset(a, 0, 256);
        sprintf(a, "// line %d\n", parser->_originRules[i1]->lineId);
        WriteFile(fd, a); // 写 {} 块
        memset(a, 0, 256);
        std::string g = parser->funcReplace(parser->_rules[i1]);
        sprintf(a, "//block\n      {\n %s \n      }\n", g.c_str());
        WriteFile(fd, a);

        WriteFile(fd, "      break;\n");

        delete[] a;
    }
    WriteFile(fd, "    }");
    WriteFile(fd, "    syms.push(item);\n");

    WriteFile(fd, "\n");
    WriteFile(fd, "    int curStateId = states.top();\n");
    {
        char* a = new char[256];
        sprintf(a, "    int nextStateId = goto_table[curStateId][rule_left_id - %d];\n", Symtab::ntoken());
        WriteFile(fd, a);
        delete[] a;
    }
    WriteFile(fd, "    states.push(nextStateId);\n");
    WriteFile(fd, "    return true;\n");
    WriteFile(fd, "}\n");
    CloseFile(fd);
}

void
Output::writeCode(FILE* f) {
    WriteFile(f, codeBlock.c_str());
}
void
Output::writeUnion(FILE* f) {
    WriteFile(f, "union YYSTYPE {\n");
    WriteFile(f, unionBlock.c_str());
    WriteFile(f, "};\n\n");
    WriteFile(f, "extern union YYSTYPE yylval;\n");
}

void
Output::writeTokEnum(FILE* f) {
    std::vector<Symbol> d;
    WriteFile(f, "enum yytokentype {\n");
    for (auto it = Symtab::_data.begin(); it != Symtab::_data.end(); it++) {
        if (it->second->clazz == token && it->second->id > 1) {
            d.push_back(it->second);
        }
    }

    std::sort(d.begin(), d.end(), [](Symbol l, Symbol r) -> bool { return l->id < r->id; });

    for (auto it = d.begin(); it != d.end(); it++) {

        char* buf = new char[256];
        sprintf(buf, "    %15s = %3d,\n", (*it)->name.c_str(), (*it)->id);
        WriteFile(f, buf);
        delete[] buf;
    }

    WriteFile(f, "    };\n");
}

void
Output::writeMatrix(FILE* f) {
}
void
Output::writeMethods(FILE* f) {
}
void
Output::writeOther(FILE* f) {
    WriteFile(f, "// code part \n");
    WriteFile(f, other.c_str());
}
