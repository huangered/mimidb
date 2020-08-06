#include "g.h"

_EXTERN_C

#include "storage/bufmgr.h"
#include "access/btree.h"
#include "util/mctx.h"
#include "storage/freespace.h"
#include "util/sysdbg.h"

_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(btree, basic)
{
    MemoryContextInit();
    BufferInit();
    
    Relation rel = (Relation)palloc(sizeof(Relation));
    rel->rnode = 1;
    rel->root_blkno = INVALID_BLOCK;

    for (int i = 0; i < 100; i++) {
        RecordPageWithFreeSpace(rel, i, BLKSZ);
    }

    for (int i = 0; i < 1000; i++) {
        //printf("%d\r\n", i);
        bool result = btinsert(rel, i, i * 10);
        EXPECT_TRUE(result);
    }

    //debug_rel(rel);
    int value;

    for (int i = 0; i < 1000; i++) {
        btgettuple(rel, i, &value);
        EXPECT_EQ(value, i * 10);
    }
}