#include "../g.hpp"

extern "C" {
#include "access/btree.h"
#include "storage/bufmgr.h"
#include "storage/freespace.h"
#include "storage/smgr.h"
}
// test the basic usage in buff mgr.
TEST(btree, incr_insert) {
    Relation rel = new RelationData{};
    rel->rd_id   = BTREE_REL_ID_1;
    rel->rd_node = { DB_ID, rel->rd_id };
    RelationOpenSmgr(rel);

    rel->index_am = GetIndexAmRoutine(0);
    rel->index_am->ambuild(rel, rel);

    for (int i = 0; i < 1000; i++) {
        bool result = rel->index_am->aminsert(rel, i, i);
        EXPECT_TRUE(result);
    }

    for (int i = 0; i < 1000; i++) {
        IndexScanDesc scan = rel->index_am->ambeginscan(rel, 1, nullptr);
        scan               = new IndexScanDescData{};
        scan->index_rel    = rel;
        scan->key          = i;
        scan->block        = INVALID_BLOCK;
        bool result        = rel->index_am->amgetnext(scan, ScanDirection::Forward);

        EXPECT_EQ(i, scan->value);
        delete scan;
    }

    delete rel;
}

TEST(btree, decr_insert) {
    Relation rel = new RelationData{};
    rel->rd_id   = BTREE_REL_ID_2;
    rel->rd_node = { DB_ID, rel->rd_id };
    RelationOpenSmgr(rel);

    rel->index_am = GetIndexAmRoutine(0);
    rel->index_am->ambuild(rel, rel);

    for (int i = 10; i > 0; i--) {
        // printf("insert %d\r\n", i);
        bool result = rel->index_am->aminsert(rel, i, i);
        EXPECT_TRUE(result);
    }

    IndexScanDesc scan = new IndexScanDescData;
    scan->index_rel    = rel;
    scan->key          = 5;
    scan->block        = INVALID_BLOCK;
    bool result        = rel->index_am->amgetnext(scan, ScanDirection::Forward);

    EXPECT_EQ(5, scan->value);
    delete scan;
    delete rel;
}

TEST(btree, blk_insert) {
    Relation rel = (Relation)palloc0(sizeof(RelationData));
    rel->rd_id   = BTREE_REL_ID_3;
    rel->rd_node = { DB_ID, rel->rd_id };
    RelationOpenSmgr(rel);

    rel->index_am = GetIndexAmRoutine(0);
    rel->index_am->ambuild(rel, rel);

    for (int i{}; i < 10; i++) {
        // printf("insert %d\r\n", i);
        bool result = rel->index_am->aminsert(rel, i, i);
        EXPECT_TRUE(result);
    }

    IndexScanDesc scan = (IndexScanDesc)palloc0(sizeof(IndexScanDescData));
    scan->index_rel    = rel;
    scan->key          = 5;
    scan->block        = INVALID_BLOCK;
    bool result        = rel->index_am->amgetnext(scan, ScanDirection::Forward);

    EXPECT_EQ(5, scan->value);
    pfree(scan);
    pfree(rel);
}
