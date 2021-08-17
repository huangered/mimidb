AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_executable(sql ${DIR_SRCS})

target_link_libraries(sql c_util)
