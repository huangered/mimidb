FILE(GLOB sources */*.cpp)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_library(util ${sources} ${DIR_SRCS})
