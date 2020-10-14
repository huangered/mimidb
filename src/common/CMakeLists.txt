AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_library(common ${DIR_SRCS})
target_link_libraries(common)