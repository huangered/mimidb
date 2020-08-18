#include "g.h"

_EXTERN_C

#include "storage/bufmgr.h"
#include "access/btree.h"
#include "util/mctx.h"
#include "storage/freespace.h"
#include "util/sysdbg.h"

_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(btree, incr_insert)
{
    MemoryContextInit();
    BufferInit();

    Relation rel = (Relation)palloc(sizeof(Relation));
    rel->rnode = 1;
    rel->root_blkno = P_NONE;
    rel->index_am = buildRoute();
    btbuildempty(rel);

    for (int i = 0; i < 100; i++) {
        RecordPageWithFreeSpace(rel, i, BLKSZ);
    }

    for (int i = 0; i < 1000; i++) {
        //printf("%d\r\n", i);
        bool result = rel->index_am->insert(rel, i, i);
        EXPECT_TRUE(result);
    }

    //debug_rel(rel);
}

TEST(btree, decr_insert)
{
    MemoryContextInit();
    BufferInit();

    Relation rel = (Relation)palloc(sizeof(Relation));
    rel->rnode = 1;
    rel->root_blkno = P_NONE;
    btbuildempty(rel);

    for (int i = 0; i < 100; i++) {
        RecordPageWithFreeSpace(rel, i, BLKSZ);
    }

    for (int i = 0; i < 1000; i++) {
        //printf("%d\r\n", i);
        bool result = rel->index_am->insert(rel, i, i);
        EXPECT_TRUE(result);
    }

    //debug_rel(rel);
 
    for (int i = 0; i < 1000; i++) {
        IndexScanDesc scan = (IndexScanDesc)palloc(sizeof(IndexScanDescData));
        scan->index_rel = rel;
        scan->key = i;
        scan->block = INVALID_BLOCK;
        bool result = rel->index_am->gettuple(scan);
        EXPECT_TRUE(result);
        EXPECT_EQ(scan->value, i);
        result = rel->index_am->gettuple(scan);
        EXPECT_FALSE(result);
        pfree(scan);
    }
}