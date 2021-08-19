#include "sema.hpp"
#include "reader.hpp"
#include "output.hpp"
#include "rev4.hpp"

int
main(int argc, char* argv[]) {
    FILE* f         = OpenFile("C:\\work\\mimidb\\sql-lex.rule", "r");
    const char* str = ReadFile(f);
    CloseFile(f);
    
    Node a = raw_parse(str);
    printf("%s", a->Name().c_str());
    LexNode* lex = dynamic_cast<LexNode*>(a);
    std::map<std::string, std::string> typeMap = lex->GetTypeMap();
    std::vector<SimpleRule> rules              = lex->GetRules();

    printf("type map: {%zd}, rules: {%zd}", typeMap.size(), rules.size());

    Parser parser2(rules);
    parser2.SetTypeMap(typeMap);
    parser2.GenerateParseTable();
    // parser.GenerateCppCode("code.hpp");
    Output output2(&parser2);
    auto j = lex->GetCode();
    output2.SetCode(lex->GetCode());
    output2.SetUnion(lex->GetUnion());
    output2.output("rev4.hpp");


    Symtab::Print();
    return 0;
}