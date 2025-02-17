#include "sema.hpp"
#include "reader.hpp"
#include "output.hpp"
#include "c.tab.hpp"
#include "symtab.hpp"
#include <cstring>
#include <cassert>
#include <iostream>
using std::string;

int
main(int argc, char* argv[]) {
    const char* fpath = "/Users/peter/Desktop/mimidb/mison/test.rule";
    // argv[1];
    const char* foutput = "output.txt";

    Symtab::Init();
    FILE* f         = OpenFile(fpath, "r");
    const char* str = ReadFile(f);
    CloseFile(f);
    Parser p(new Lexer(str, strlen(str)));
    Node a = p.parse();
    assert(a);
    printf("%s\n", a->_value.c_str());
    LexNode* lex = dynamic_cast<LexNode*>(a);
    assert(lex);
    std::map<string, string> typeMap = lex->GetTypeMap();
    Rules                            = lex->GetRules();

    for (Rule r : Rules) {
        r->print();
    }

    printf("type map: {%zd}, rules: {%zd}\n", typeMap.size(), Rules.size());
    for (auto iter = typeMap.begin(); iter != typeMap.end(); iter++) {
        std::cout << iter->first << " " << iter->second << std::endl;
    }
    SemaParser parser{ typeMap };

    parser.GenerateParseTable();

    Output output(&parser);
    output.SetCode(lex->GetCode());
    output.SetUnion(lex->GetUnion());
    output.SetOther(lex->other);
    output.SetParam(lex->param);
    output.OutputFile(foutput);

    Symtab::Print();
    return 0;
}
