#include "sema.hpp"
#include "reader.hpp"
#include "output.hpp"
#include "c.tab.hpp"
#include "symtab.hpp"

using std::string;

int
main(int argc, char* argv[]) {
    Symtab::Init();
#ifdef _WIN32
    FILE* f         = OpenFile("C:\\work\\mimidb\\sql-lex.rule", "r");
#else
    FILE* f         = OpenFile("../sql-lex.rule", "r");
#endif
    const char* str = ReadFile(f);
    CloseFile(f);
    Parser p;
    Node a = p.parse(str);
    printf("%s\n", a->_value.c_str());
    LexNode* lex                     = dynamic_cast<LexNode*>(a);
    std::map<string, string> typeMap = lex->GetTypeMap();
    std::vector<Rule> rules          = lex->GetRules();

    printf("type map: {%zd}, rules: {%zd}\n", typeMap.size(), rules.size());

    SemaParser parser2(rules);
    parser2.SetTypeMap(typeMap);
    parser2.GenerateParseTable();

    Output output2(&parser2);
    auto j = lex->GetCode();
    output2.SetCode(lex->GetCode());
    output2.SetUnion(lex->GetUnion());
    output2.SetOther(lex->other);
    output2.SetParam(lex->param);
    output2.OutputFile("rev4.hpp");

    Symtab::Print();
    return 0;
}
