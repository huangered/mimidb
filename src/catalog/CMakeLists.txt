FILE(GLOB sources *.c)

add_library(catalog ${sources})
target_link_libraries(catalog access)