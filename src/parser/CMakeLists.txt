add_custom_command (
  OUTPUT "c.tab.cpp"
  COMMAND mison ${PROJECT_SOURCE_DIR}/src/parser/parser.rule ${PROJECT_SOURCE_DIR}/src/parser/
  COMMAND m4 -I ${PROJECT_SOURCE_DIR}/data -I ${PROJECT_SOURCE_DIR}/src/parser ${PROJECT_SOURCE_DIR}/data/hpp.m4 > c.tab.hpp
  COMMAND m4 -I ${PROJECT_SOURCE_DIR}/data -I ${PROJECT_SOURCE_DIR}/src/parser ${PROJECT_SOURCE_DIR}/data/cpp.m4 > c.tab.cpp
  COMMENT "build header & cpp"
)

add_library(parser  "c.tab.cpp"
  "lexer.cpp"
  "parse_param.cpp" 
  "parse_expr.cpp"
  "parse_stmt.cpp"
  )
