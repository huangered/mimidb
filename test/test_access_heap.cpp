#include "g.h"

_EXTERN_C

#include "storage/bufmgr.h"
#include "access/heap.h"
#include "util/mctx.h"
#include "storage/freespace.h"
#include "util/sysdbg.h"
#include "util/mctx.h"
#include "access/tbapi.h"

_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(heap, incr_insert)
{
    MemoryContextInit();
    BufferInit();

    Relation rel = (Relation)palloc(sizeof(RelationData));
    rel->rnode = 2;
    rel->tb_am = table_route();
    rel->root_blkno = 1;
    for (int i = 0; i < 100; i++) {
        RecordPageWithFreeSpace(rel, i, BLKSZ);
    }

    for (int i = 0; i < 100; i++) {
        //printf("%d\r\n", i);
        TupleSlotDesc* slot = (TupleSlotDesc*)palloc(sizeof(TupleSlotDesc));
        slot->key = i;
        slot->value = i;
        bool result = rel->tb_am->tuple_insert(rel, slot);
        EXPECT_TRUE(result);
        pfree(slot);
    }

    print_heap(rel);

    HeapScanDesc scan = (HeapScanDesc)palloc(sizeof(HeapScanDescData));
    scan->rel = rel;
    scan->inited = false;
    scan->num_blocks = 1;
    scan->key = 99;
    EXPECT_TRUE(heapgettuple(scan));
    EXPECT_EQ(scan->value, 99);
    pfree(scan);
    pfree(rel->tb_am);
    pfree(rel);
}
