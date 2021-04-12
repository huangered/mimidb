#include "../g.hpp"

#include "storage/bufmgr.hpp"
#include "access/heap.hpp"
#include "access/rel.hpp"
#include "storage/smgr.hpp"
#include "util/mctx.hpp"

// test the basic usage in buff mgr.
TEST(heap, incr_insert)
{
    // insert
    Relation rel = new RelationData{};
    rel->rd_id = 2000;
    rel->rd_node = { 0, rel->rd_id };
    rel->tb_am = HeapRoute();

    RelationOpenSmgr(rel);

    Form_mimi_attribute attr = new FormData_mimi_attribute[2]{};
    attr[0].att_len = sizeof(int);
    attr[1].att_len = sizeof(int);

    rel->tupleDesc = CreateTupleDesc(2, attr);
    delete[] attr;

    for (int i = 0; i < 5; i++) {
        int* value = new int[2]{ 0,i };
        HeapTuple tuple = heap_form_tuple(rel->tupleDesc, (Datum*)value);
        bool result = rel->tb_am->Insert(rel, tuple);
        EXPECT_TRUE(result);
        heap_free_tuple(tuple);
        delete[] value;
    }
    // find
    Datum datum = IntGetDatum(0);
    ScanKey skey = new ScanKeyData;
    ScanKeyInit(skey, 0, BTEqualStrategyNumber, datum, 0);
    HeapScanDesc hsDesc = rel->tb_am->BeginScan(rel, 1, skey);
    for (int i{}; i < 5; i++) {
        HeapTuple htup = rel->tb_am->GetNext(hsDesc);
        //printf("min %d\r\n", htup->t_data->t_heap.t_xmin);
        //printf("max %d\r\n", htup->t_data->t_heap.t_xmax);
        // 验证htup
        char* data = (char*)htup->t_data + HEAP_TUPLE_HEADER_SIZE;
        int* j = (int*)data;
        int* l = j + 1;
        EXPECT_EQ(datum, *j);
        EXPECT_EQ(i, *l);
    }

    rel->tb_am->EndScan(hsDesc);

    //if (htup)
    //    delete htup;
    delete skey;

    FreeTupleDesc(rel->tupleDesc);
    delete rel;
}