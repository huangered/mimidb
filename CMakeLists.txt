cmake_minimum_required (VERSION 3.8)

project ("mimi_db")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC) 
  add_compile_options("/std:c++latest")
else()
  add_compile_options("-std=c++17")
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories("include")

add_subdirectory(src)
add_subdirectory("test")