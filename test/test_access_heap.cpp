#include "g.h"

_EXTERN_C

#include "storage/bufmgr.h"
#include "access/heap.h"
#include "util/mctx.h"
#include "storage/freespace.h"
#include "util/sysdbg.h"

_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(heap, incr_insert)
{
    MemoryContextInit();
    BufferInit();

    Relation rel = (Relation)palloc(sizeof(Relation));
    rel->rnode = 2;
    rel->root_blkno = 1;

    for (int i = 0; i < 100; i++) {
        RecordPageWithFreeSpace(rel, i, BLKSZ);
    }

    for (int i = 0; i < 10; i++) {
        //printf("%d\r\n", i);
        bool result = heapinsert(rel, i, i);
        EXPECT_TRUE(result);
    }

    print_heap(rel);
}
