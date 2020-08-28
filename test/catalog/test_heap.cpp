#include "../g.h"

_EXTERN_C

#include "catalog/heap.h"
#include "util/mctx.h"
#include "storage/bufmgr.h"
#include "storage/freespace.h"
#include "catalog/mimi_code.h"

_END_EXTERN_C

TEST(Catalog, heap) {
    BufferInit();
    RelationCacheInit();

    Relation mrel = (Relation)palloc(sizeof(RelationData));
    mrel->rnode = ClassRelationId;

    for (int i = 0; i < 100; i++) {
        RecordPageWithFreeSpace(mrel, i, BLKSZ);
    }

    pfree(mrel);

    TupleDesc tupdesc = (TupleDesc)palloc(sizeof(TupleDescData));
    tupdesc->natts = 0;
    Relation rel = heap_create("test", 10000, tupdesc);
    
    EXPECT_NE(rel, nullptr);


    pfree(rel);
    pfree(tupdesc);
}