#include "../g.h"

_EXTERN_C

#include "catalog/heap.h"
#include "util/mctx.h"
#include "storage/bufmgr.h"

_END_EXTERN_C

TEST(Catalog, heap) {
    BufferInit();
    RelationCacheInit();

    TupleDesc tupdesc = (TupleDesc)palloc(sizeof(TupleDescData));
    tupdesc->natts = 0;
    Relation rel = heap_create("test", 100, tupdesc);
    
    EXPECT_NE(rel, nullptr);

    pfree(rel);
    pfree(tupdesc);
}