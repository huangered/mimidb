find_package (Python COMPONENTS)
execute_process(COMMAND python "${CMAKE_CURRENT_SOURCE_DIR}/catalog.py")

FILE(GLOB sources *.cpp)

add_library(catalog ${sources})
target_link_libraries(catalog access)