#include "sema.hpp"
#include "reader.hpp"
#include "output.hpp"
#include "rev1.hpp"

int
main(int argc, char* argv[]) {

    auto rList = ReadRules("C:\\work\\mimidb\\sql-lex2.rule");

    Parser parser(rList.rules);
    parser.SetTypeMap(rList.typeMap);
    parser.GenerateParseTable();
   // parser.GenerateCppCode("code.hpp");
    Output output(&parser);
    output.output("rev1.hpp");

    //const char* str = "@token a % @type str a @type node T % T : a { }";
    FILE* f         = OpenFile("C:\\work\\mimidb\\sql-lex.rule", "r");
    const char* str = ReadFile(f);
    CloseFile(f);
    
    Node a = raw_parse(str);
    printf("%s", a->Name().c_str());
    LexNode* lex = dynamic_cast<LexNode*>(a);
    std::map<std::string, std::string> typeMap = lex->GetTypeMap();
    std::vector<SimpleRule> rules              = lex->GetRules();

    printf("type map: {%d}, rules: {%d}", typeMap.size(), rules.size());
    return 0;
}