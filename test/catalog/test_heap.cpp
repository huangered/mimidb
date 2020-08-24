#include "../g.h"

_EXTERN_C

#include "catalog/heap.h"

_END_EXTERN_C

TEST(Catalog, heap) {
    Relation rel = heap_create("test", 1);
    EXPECT_EQ(rel, nullptr);
}