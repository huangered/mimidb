FILE(GLOB sources */*.c)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_library(c_util ${sources} ${DIR_SRCS})