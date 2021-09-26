FILE(GLOB sources */*.cpp)

add_library(storage ${sources} )
target_link_libraries(storage port util)
