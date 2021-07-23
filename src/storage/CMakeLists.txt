FILE(GLOB sources */*.cpp */*.c)

add_library(storage ${sources} )
target_link_libraries(storage port util)