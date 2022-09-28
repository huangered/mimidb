message("fff ${CMAKE_CURRENT_BINARY_DIR}")
add_custom_command (
  OUTPUT "c.tab.cpp" "c.tab.hpp"
  COMMAND ${CMAKE_BINARY_DIR}/bin/mison ${PROJECT_SOURCE_DIR}/src/parser/parser.rule ./
  COMMAND m4 -I ${PROJECT_SOURCE_DIR}/data -I ${PROJECT_SOURCE_DIR}/src/parser ${PROJECT_SOURCE_DIR}/data/hpp.m4 > c.tab.hpp
  COMMAND m4 -I ${PROJECT_SOURCE_DIR}/data -I ${PROJECT_SOURCE_DIR}/src/parser ${PROJECT_SOURCE_DIR}/data/cpp.m4 > c.tab.cpp
  DEPENDS  ${CMAKE_CURRENT_SOURCE_DIR}/parser.rule
  COMMENT "build header & cpp"
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(parser "c.tab.cpp"
  "lexer.cpp"
  "parse_param.cpp" 
  "parse_expr.cpp"
  "parse_stmt.cpp"
  )
