#include "../g.hpp"

#include "access/btree.hpp"
#include "storage/bufmgr.hpp"
#include "storage/freespace.hpp"
#include "storage/smgr.hpp"
#include "util/mctx.hpp"
#include "util/sysdbg.hpp"

// test the basic usage in buff mgr.
TEST(btree, incr_insert)
{
    Relation rel = new RelationData{};
    rel->rd_id = 10000;
    rel->rd_node = { 10000, 10000 };
    RelationOpenSmgr(rel);

    rel->index_am = BtreeRoute();
    rel->index_am->BuildEmpty(rel);

    for (int i = 0; i < 100; i++) {
        //printf("insert %d\r\n", i);
        bool result = rel->index_am->Insert(rel, i, i);
        EXPECT_TRUE(result);
    }

    IndexScanDesc scan = new IndexScanDescData;
    scan->index_rel = rel;
    scan->key = 5;
    scan->block = INVALID_BLOCK;
    bool result = rel->index_am->GetTuple(scan);

    EXPECT_EQ(5, scan->value);
    delete scan;
    delete rel;
}

TEST(btree, decr_insert)
{
    Relation rel = new RelationData{};
    rel->rd_id = 20000;
    rel->rd_node = { 10000, 20000 };
    RelationOpenSmgr(rel);

    rel->index_am = BtreeRoute();
    rel->index_am->BuildEmpty(rel);

    for (int i = 100; i > 0; i--) {
        //printf("insert %d\r\n", i);
        bool result = rel->index_am->Insert(rel, i, i);
        EXPECT_TRUE(result);
    }

    IndexScanDesc scan = new IndexScanDescData;
    scan->index_rel = rel;
    scan->key = 5;
    scan->block = INVALID_BLOCK;
    bool result = rel->index_am->GetTuple(scan);

    EXPECT_EQ(5, scan->value);
    delete scan;
    delete rel;
}

TEST(btree, blk_insert)
{
    Relation rel = new RelationData{};
    rel->rd_id = 30000;
    rel->rd_node = { 10000, 30000 };
    RelationOpenSmgr(rel);

    rel->index_am = BtreeRoute();
    rel->index_am->BuildEmpty(rel);

    for (int i{}; i < 1000; i++) {
        //printf("insert %d\r\n", i);
        bool result = rel->index_am->Insert(rel, i, i);
        EXPECT_TRUE(result);
    }

    IndexScanDesc scan = new IndexScanDescData{};
    scan->index_rel = rel;
    scan->key = 5;
    scan->block = INVALID_BLOCK;
    bool result = rel->index_am->GetTuple(scan);

    EXPECT_EQ(5, scan->value);
    delete scan;
    delete rel;
}