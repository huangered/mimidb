#include "../g.hpp"

#include "catalog/heap.hpp"

TEST(heap_catalog, heap_create) {
    TupleDesc tupdesc = new TupleDescData{ 2 };
    
    //Relation rel = heap_create_with_catalog("test", 10003, tupdesc);

    delete tupdesc;
}