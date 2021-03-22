#include "../g.hpp"

#include "access/rel.hpp"
#include "storage/bufmgr.hpp"
#include "access/btree.hpp"

// test the basic usage in buff mgr.
TEST(buff_mgr, basic)
{
    BufferMgr mgr{};
    Relation rel = new RelationData;
    rel->rd_id = 1;
    rel->rd_node.dbNode = 1;
    rel->rd_node.relNode = 2;
    rel->rd_smgr = nullptr;
    Buffer buf_id = mgr.ReadBuffer(rel, 0);

    EXPECT_EQ(buf_id, 1);

    buf_id = mgr.ReadBuffer(rel, 0);

    EXPECT_EQ(buf_id, 1);

    Buffer buf_id_2 = mgr.ReadBuffer(rel, 1);
    EXPECT_EQ(buf_id_2, 2);

    mgr.ReleaseBuffer(buf_id);
    mgr.ReleaseBuffer(buf_id);
    mgr.ReleaseBuffer(buf_id_2);
    delete rel;
}

TEST(buff_mgr, p_new)
{
    BufferMgr mgr{};
    Relation rel = new RelationData;
    rel->rd_id = 2;
    rel->rd_node.dbNode = 10;
    rel->rd_node.relNode = 20;
    rel->rd_smgr = nullptr;

    Buffer buf_id = mgr.ReadBuffer(rel, P_NEW);
    Buffer buf_id2 = mgr.ReadBuffer(rel, P_NEW);

    EXPECT_EQ(buf_id, 1);
    EXPECT_EQ(buf_id2, 2);

    mgr.ReleaseBuffer(buf_id);
    mgr.ReleaseBuffer(buf_id2);

    delete rel;
}