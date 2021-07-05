AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_library(lex ${DIR_SRCS})

#target_link_libraries(server access catalog common port storage util)