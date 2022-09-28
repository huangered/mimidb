AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_executable(mison ${DIR_SRCS})

add_custom_target(
  build_m4 ALL
  COMMAND mison ${PROJECT_SOURCE_DIR}/mison/mison.rule ./
  COMMAND m4 -I ${PROJECT_SOURCE_DIR}/data -I . ${PROJECT_SOURCE_DIR}/data/hpp.m4 > c.tab.hpp
  COMMAND m4 -I ${PROJECT_SOURCE_DIR}/data -I . ${PROJECT_SOURCE_DIR}/data/cpp.m4 > c.tab.cpp

  COMMAND clang-format -i c.tab.hpp
  COMMAND clang-format -i c.tab.cpp
  
  COMMENT "build header and cpp"

  COMMAND cp c.tab.hpp ${PROJECT_SOURCE_DIR}/mison/
  COMMAND cp c.tab.cpp ${PROJECT_SOURCE_DIR}/mison/
)

INSTALL(TARGETS mison
  RUNTIME DESTINATION bin
)