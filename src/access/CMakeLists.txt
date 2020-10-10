FILE(GLOB sources */*.c)

add_library(access ${sources})
target_link_libraries(access storage util)

