#include "sema.hpp"
#include "rulereader.hpp"
#include "output.hpp"

int
main(int argc, char* argv[]) {

    auto rList = ReadRules("C:\\work\\mimidb\\sql.rule");

    Parser parser(rList.rules);
    parser.SetTypeMap(rList.typeMap);
    parser.GenerateParseTable();
   // parser.GenerateCppCode("code.hpp");
    Output output(&parser);
    output.output("a.txt");

       
    return 0;
}