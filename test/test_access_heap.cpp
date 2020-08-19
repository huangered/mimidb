#include "g.h"

_EXTERN_C

#include "storage/bufmgr.h"
#include "access/heap.h"
#include "util/mctx.h"
#include "storage/freespace.h"
#include "util/sysdbg.h"
#include "util/mctx.h"

_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(heap, incr_insert)
{
    MemoryContextInit();
    BufferInit();

    Relation rel = (Relation)palloc(sizeof(RelationData));
    rel->rnode = 2;

    for (int i = 0; i < 100; i++) {
        RecordPageWithFreeSpace(rel, i, BLKSZ);
    }

    for (int i = 0; i < 100; i++) {
        //printf("%d\r\n", i);
        bool result = heapinsert(rel, i, i);
        EXPECT_TRUE(result);
    }

    print_heap(rel);

    HeapScanDesc scan = (HeapScanDesc)palloc(sizeof(HeapScanDescData));
    scan->rel = rel;
    scan->inited = false;
    scan->num_blocks = 1;
    scan->key = 10;
    EXPECT_TRUE(heapgettuple(scan));
    EXPECT_EQ(scan->value[0], 10);
    EXPECT_EQ(scan->num_value, 1);
    pfree(scan->value);
    pfree(scan);
}
