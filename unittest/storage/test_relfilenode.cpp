#include "../g.hpp"
#include "storage/relfilenode.h"

TEST(relfilenode, basic) {
    RelFileNode a{ 1, 2 }, b{ 1, 2 }, c{ 2, 3 };
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}