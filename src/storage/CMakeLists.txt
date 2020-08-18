FILE(GLOB sources */*.c)

add_library(storage ${sources} )
target_link_libraries(storage port)
