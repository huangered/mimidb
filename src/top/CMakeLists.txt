AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_library(top ${DIR_SRCS})

target_link_libraries(top access catalog common port storage util parser)