#include "sema.hpp"
#include "rulereader.hpp"
#include "output.hpp"
#include "rev1.hpp"

int
main(int argc, char* argv[]) {

    auto rList = ReadRules("C:\\work\\mimidb\\sql-lex.rule");

    Parser parser(rList.rules);
    parser.SetTypeMap(rList.typeMap);
    parser.GenerateParseTable();
   // parser.GenerateCppCode("code.hpp");
    Output output(&parser);
    output.output("rev1.hpp");

    //Node a = raw_parse("abcd");
       
    return 0;
}