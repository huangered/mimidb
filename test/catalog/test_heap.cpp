#include "../g.h"

_EXTERN_C

#include "catalog/heap.h"
#include "util/mctx.h"

_END_EXTERN_C

TEST(Catalog, heap) {
    TupleDesc desc = (TupleDesc)palloc(sizeof(TupleDescData));
    desc->natts = 0;
    Relation rel = heap_create("test", 1, desc);
    //EXPECT_NE(rel, nullptr);

    pfree(desc);
    pfree(rel);
}