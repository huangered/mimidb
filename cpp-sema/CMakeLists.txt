AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_executable(cppsema ${DIR_SRCS})

add_custom_target(
  asdf ALL
  COMMAND cppsema
  COMMAND m4 -I ../data -I . ../data/hpp.m4 > c.tab.hpp
  COMMAND m4 -I ../data -I . ../data/cpp.m4 > c.tab.cpp
  COMMENT "build header and cpp"
)

