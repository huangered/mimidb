#include "../g.h"

_EXTERN_C

#include "catalog/heap.h"
#include "util/mctx.h"
#include "storage/bufmgr.h"
#include "storage/freespace.h"
#include "storage/smgr.h"
#include "catalog/mimi_code.h"

_END_EXTERN_C

TEST(Catalog, heap) {
    BufferInit();
    RelationCacheInit();

    Relation mrel = (Relation)palloc(sizeof(RelationData));
    mrel->rnode = ClassRelationId;
    mrel->rd_smgr = (SmgrRelation)palloc(sizeof(SMgrRelationData));
    mrel->rd_smgr->smgr_fsm_nblocks = 0;

    RecordPageWithFreeSpace(mrel, 0, BLKSZ);
    FreeSpaceMapVacuumRange(mrel, 0, 1);

    pfree(mrel);

    TupleDesc tupdesc = (TupleDesc)palloc(sizeof(TupleDescData));
    tupdesc->natts = 0;
    Relation rel = heap_create_with_catalog("test", 10000, tupdesc);
    
    EXPECT_NE(rel, nullptr);


    pfree(rel);
    pfree(tupdesc);
}