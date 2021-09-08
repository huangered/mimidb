cmake_minimum_required (VERSION 3.8)

project ("mimi_db")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

if(MSVC) 
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++11")
else()
  set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories("include")

add_subdirectory(abseil-cpp)
add_subdirectory(mison)
add_subdirectory(src)
add_subdirectory(unittest)
