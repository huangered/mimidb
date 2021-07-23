#include "sema/sema.hpp"
#include "sema/rulereader.hpp"

int
main(int argc, char* argv[]) {

    auto rList = ReadRules("C:\\work\\mimidb\\sql.rule");

    Parser parser(rList);
    parser.GenerateParseTable();
    parser.GenerateCppCode("code.cpp");

    return 0;
}