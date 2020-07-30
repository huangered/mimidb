#include <gtest/gtest.h>

_EXTERN_C
#include "port/shmem.h"
_END_EXTERN_C

TEST(share_memory_test, ShareMem) {
    shmem_init(100);
    shmem_close();
}