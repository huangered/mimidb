#include "../g.hpp"

#include "access/heap.hpp"
#include "access/rel.hpp"
#include "catalog/heap.hpp"
#include "storage/smgr.hpp"
#include "util/mctx.hpp"
// test the basic usage in buff mgr.
TEST(heap, incr_insert)
{
    Relation rel = heap_create_with_catalog("test", 10000, nullptr);

    rel = relation_open(10000);
    RelationOpenSmgr(rel);

    Form_mimi_attribute attr = new FormData_mimi_attribute[2]{};
    attr[0].att_len = sizeof(int);
    attr[1].att_len = sizeof(int);

    rel->tupleDesc = CreateTupleDesc(2, attr);
    delete[] attr;

    for (int i = 0; i < 1000; i++) {
        int* value = new int[2]{ i, i * 10 };
        HeapTuple tuple = heap_form_tuple(rel->tupleDesc, (Datum*)value);
        bool result = rel->tb_am->Insert(rel, tuple);
        EXPECT_TRUE(result);
        heap_free_tuple(tuple);
        delete[] value;
    }
    // find
    Datum datum = IntGetDatum(0);
    ScanKey skey = (ScanKey)palloc0(sizeof(ScanKeyData));
    ScanKeyInit(skey, 0, BTEqualStrategyNumber, datum, 2);
    HeapScanDesc hsDesc = rel->tb_am->BeginScan(rel, 1, skey);
    for (int i{}; i < 5; i++) {
        HeapTuple htup = rel->tb_am->GetNext(hsDesc, ScanDirection::Forward);
        if (htup->t_data != nullptr) {
            char* data = (char*)htup->t_data + HEAP_TUPLE_HEADER_SIZE;
            int* j = (int*)data;
            int* l = j + 1;
            EXPECT_EQ(datum, *j);
            EXPECT_EQ(datum * 10, *l);
        }
    }

    rel->tb_am->EndScan(hsDesc);

    //rel->tb_am->debug(rel);

    //if (htup)
    //    delete htup;
    pfree(skey);

    FreeTupleDesc(rel->tupleDesc);
    delete rel;
}