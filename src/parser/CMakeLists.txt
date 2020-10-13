find_package(BISON)
find_package(FLEX)

BISON_TARGET(MyParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)

FLEX_TARGET(MyScanner flex.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.c COMPILE_FLAGS "--nounistd")

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)


add_library(parser ${BISON_MyParser_OUTPUTS}
                   ${FLEX_MyScanner_OUTPUTS}
                   "parse_param.c" 
                   "parse_expr.c"
                   "parse_stmt.c")
target_link_libraries(parser util)