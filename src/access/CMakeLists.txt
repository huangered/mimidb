FILE(GLOB sources */*.cpp)

add_library(access ${sources})
target_link_libraries(access storage util)