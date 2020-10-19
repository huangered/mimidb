#include "../g.h"

_EXTERN_C

#include "storage/bufmgr.h"
#include "access/heap.h"
#include "util/mctx.h"
#include "storage/freespace.h"
#include "storage/smgr.h"
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
    rel->rnode = 10003;
    rel->tb_am = table_route();
    rel->root_blkno = 0;

    rel->rd_smgr = (SmgrRelation)palloc(sizeof(SMgrRelationData));
    rel->rd_smgr->smgr_fsm_nblocks = 0;

    rel->tupleDesc = (TupleDesc)palloc(sizeof(TupleDescData));
    rel->tupleDesc->natts = 2;
    rel->tupleDesc->attr[0].attlen = 4;
    rel->tupleDesc->attr[1].attlen = 4;

    RecordPageWithFreeSpace(rel, 0, BLKSZ);
    FreeSpaceMapVacuumRange(rel, 0, 1);

    for (int i = 0; i < 10; i++) {
        //printf("%d\r\n", i);
        TupleSlotDesc* slot = (TupleSlotDesc*)palloc(sizeof(TupleSlotDesc));
        slot->key = i;
        slot->value = i;
        bool result = rel->tb_am->tuple_insert(rel, slot);
        EXPECT_TRUE(result);
        pfree(slot);
    }

    //print_heap(rel);

    HeapScanDesc scan = (HeapScanDesc)palloc(sizeof(HeapScanDescData));
    scan->rs_base.rs_rel = rel;
    scan->inited = false;
    scan->num_blocks = 1;
    scan->key = 9;
    EXPECT_TRUE(heapgettuple(scan));
    EXPECT_EQ(scan->value, 9);
    pfree(scan);
    pfree(rel);
}