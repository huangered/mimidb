#include <gtest/gtest.h>
#include <numeric>
#include <vector>

_EXTERN_C
#include "port/shmem.h"
_END_EXTERN_C

TEST(MyTest, Sum)
{
    std::vector<int> vec{ 1, 2, 3, 4, 5 };
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    EXPECT_EQ(sum, 15);
}

TEST(MyTest, ShareMem) {
    shmem_init(100);
    shmem_close();
}