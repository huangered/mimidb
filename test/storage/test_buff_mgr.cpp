#include "../g.hpp"

#include "access/rel.hpp"
#include "storage/bufmgr.hpp"
#include "access/btree.hpp"

// test the basic usage in buff mgr.
TEST(buff_mgr, basic)
{
    Relation rel = new RelationData{};
    rel->rd_id = 1;
    rel->rd_node = { 1,2 };
    rel->rd_smgr = nullptr;
    Buffer buf_id = ReadBuffer(rel, 1);

    EXPECT_GT(buf_id, 0);

    buf_id = ReadBuffer(rel, 1);

    EXPECT_GT(buf_id, 0);

    Buffer buf_id_2 = ReadBuffer(rel, 1);
    EXPECT_GT(buf_id_2, 0);

    ReleaseBuffer(buf_id);
    ReleaseBuffer(buf_id);
    ReleaseBuffer(buf_id_2);
    delete rel;
}

TEST(buff_mgr, p_new)
{
    Relation rel = new RelationData{};
    rel->rd_id = 2;
    rel->rd_node.dbNode = 10;
    rel->rd_node.relNode = 20;
    rel->rd_smgr = nullptr;

    Buffer buf_id = ReadBuffer(rel, P_NEW);
    Buffer buf_id2 = ReadBuffer(rel, P_NEW);

    EXPECT_GT(buf_id, 0);
    EXPECT_GT(buf_id2, 0);

    ReleaseBuffer(buf_id);
    ReleaseBuffer(buf_id2);

    delete rel;
}