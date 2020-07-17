
find_package(BISON)
if (${BISON_FOUND}) 
    message(STATUS "Found bison")
    execute_process(COMMAND bison "--help")
endif ()

find_package(FLEX)
if (${FLEX_FOUND}) 
    message(STATUS "Found flex")
    execute_process(COMMAND flex)
endif()

