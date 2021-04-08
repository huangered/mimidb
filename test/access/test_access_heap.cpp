#include "../g.hpp"

#include "storage/bufmgr.hpp"
#include "access/heap.hpp"
#include "access/rel.hpp"
#include "storage/smgr.hpp"

// test the basic usage in buff mgr.
TEST(heap, incr_insert)
{
    // insert
    Relation rel = new RelationData{};
    rel->rd_id = 2000;
    rel->rd_node = { 3000, 2000 };
    rel->tb_am = HeapRoute();

    RelationOpenSmgr(rel);

    Form_mimi_attribute attr = new FormData_mimi_attribute[2]{};
    attr[0].att_len = sizeof(int);
    attr[1].att_len = sizeof(int);

    rel->tupleDesc = CreateTupleDesc(2, attr);
    delete[] attr;

    for (int i = 0; i < 5; i++) {
        int* value = new int[2]{ i,i };
        HeapTuple tuple = heap_form_tuple(rel->tupleDesc, (Datum*)value);
        bool result = rel->tb_am->Insert(rel, tuple);
        EXPECT_TRUE(result);
        heap_free_tuple(tuple);
        delete[] value;
    }

    // find
    ScanKey skey = new ScanKeyData{};
    HeapScanDesc hsDesc = rel->tb_am->BeginScan(rel, 1, skey);
    HeapTuple htup = rel->tb_am->GetNext(hsDesc);
    // 验证htup
    rel->tb_am->EndScan(hsDesc);

    //if (htup)
    //    delete htup;

    FreeTupleDesc(rel->tupleDesc);
    delete rel;
}