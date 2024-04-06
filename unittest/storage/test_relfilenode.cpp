#include "../g.hpp"
_EXTERN_C
#include "storage/relfilenode.h"
_END_EXTERN_C

TEST(relfilenode, basic) {
    RelFileNode a{ 1, 2 }, b{ 1, 2 }, c{ 2, 3 };
    EXPECT_EQ(a.dbNode, b.dbNode);
    EXPECT_NE(a.dbNode, c.dbNode);
}