cmake_minimum_required (VERSION 3.8)

project ("mimi_db")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

if(MSVC) 
  #add_compile_options("/std:c++17")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /std:c99")
else()
  #add_compile_options("-std=c++17")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories("include")

add_subdirectory(src)
add_subdirectory("test")
