#include "g.h"

_EXTERN_C

#include "storage/bufmgr.h"
#include "access/btree.h"
#include "util/mctx.h"

_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(btree, basic)
{
    MemoryContextInit();
    BufferInit();
    Relation rel = (Relation)palloc(sizeof(Relation));
    rel->rnode = 1;


    for (int i = 0; i < 1000; i++) {
        bool result = btinsert(rel, i, i * 10);
        EXPECT_TRUE(result);
    }

    int value;

    for (int i = 0; i < 1000; i++) {
        btgettuple(rel, i, &value);
        EXPECT_EQ(value, i * 10);
    }
}