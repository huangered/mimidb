find_package(BISON)
find_package(FLEX)

BISON_TARGET(MyParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)

FLEX_TARGET(MyScanner lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)


add_library(parser ${BISON_MyParser_OUTPUTS}  ${FLEX_MyScanner_OUTPUTS})