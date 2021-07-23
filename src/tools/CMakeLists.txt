AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_executable(s1 ${DIR_SRCS})

target_link_libraries(s1 storage lexer sema)