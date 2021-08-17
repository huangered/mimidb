#include "sema.hpp"
#include "rulereader.hpp"

int
main(int argc, char* argv[]) {

    auto rList = ReadRules("C:\\work\\mimidb\\sql.rule");

    Parser parser(rList.rules);
    parser.SetTypeMap(rList.typeMap);
    parser.GenerateParseTable();
    parser.GenerateCppCode("code.hpp");

    return 0;
}