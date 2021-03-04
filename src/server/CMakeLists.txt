AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_executable(server ${DIR_SRCS})

target_link_libraries(server access catalog common port storage util)