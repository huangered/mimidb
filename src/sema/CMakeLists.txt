AUX_SOURCE_DIRECTORY(. DIR_SRCS)
add_library(sema ${DIR_SRCS})

target_link_libraries(sema lexer storage)
