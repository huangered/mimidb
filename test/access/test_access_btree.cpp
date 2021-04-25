#include "../g.hpp"

#include "access/btree.hpp"
#include "storage/bufmgr.hpp"
#include "storage/freespace.hpp"
#include "storage/smgr.hpp"
#include "util/mctx.hpp"

// test the basic usage in buff mgr.
TEST(btree, incr_insert)
{
    Relation rel = new RelationData{};
    rel->rd_id = 10000;
    rel->rd_node = { 0, rel->rd_id };
    RelationOpenSmgr(rel);

    rel->index_am = BtreeRoute();
    rel->index_am->BuildEmpty(rel);

    for (int i = 0; i < 1000; i++) {
        bool result = rel->index_am->Insert(rel, i, i);
        EXPECT_TRUE(result);
    }

    IndexScanDesc scan = rel->index_am->BeginScan(rel, 1, nullptr);
    scan = new IndexScanDescData{};
    scan->index_rel = rel;
    scan->key = 5;
    scan->block = INVALID_BLOCK;
    bool result = rel->index_am->GetNext(scan, ScanDirection::Forward);

    EXPECT_EQ(5, scan->value);
    delete scan;
    delete rel;
}

TEST(btree, decr_insert)
{
    Relation rel = new RelationData{};
    rel->rd_id = 20000;
    rel->rd_node = { 10000, rel->rd_id };
    RelationOpenSmgr(rel);

    rel->index_am = BtreeRoute();
    rel->index_am->BuildEmpty(rel);

    for (int i = 10; i > 0; i--) {
        //printf("insert %d\r\n", i);
        bool result = rel->index_am->Insert(rel, i, i);
        EXPECT_TRUE(result);
    }

    IndexScanDesc scan = new IndexScanDescData;
    scan->index_rel = rel;
    scan->key = 5;
    scan->block = INVALID_BLOCK;
    bool result = rel->index_am->GetNext(scan);

    EXPECT_EQ(5, scan->value);
    delete scan;
    delete rel;
}

TEST(btree, blk_insert)
{
    Relation rel = new RelationData{};
    rel->rd_id = 30000;
    rel->rd_node = { 10000, rel->rd_id };
    RelationOpenSmgr(rel);

    rel->index_am = BtreeRoute();
    rel->index_am->BuildEmpty(rel);

    for (int i{}; i < 10; i++) {
        //printf("insert %d\r\n", i);
        bool result = rel->index_am->Insert(rel, i, i);
        EXPECT_TRUE(result);
    }

    IndexScanDesc scan = new IndexScanDescData{};
    scan->index_rel = rel;
    scan->key = 5;
    scan->block = INVALID_BLOCK;
    bool result = rel->index_am->GetNext(scan);

    EXPECT_EQ(5, scan->value);
    delete scan;
    delete rel;
}