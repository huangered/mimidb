#include "../g.hpp"

#include "access/rel.hpp"
#include "storage/bufmgr.hpp"
#include "access/btree.hpp"

// test the basic usage in buff mgr.
TEST(hash_buff_mgr, basic)
{
    BufferMgr mgr{};
    Relation rel = new RelationData;
    rel->rnode = 1;
    rel->oid = 1;

    Buffer buf_id = mgr.ReadBuffer(rel, ForkNumber::MAIN_FORKNUM, 0);

    EXPECT_EQ(buf_id, 1);

    buf_id = mgr.ReadBuffer(rel, ForkNumber::MAIN_FORKNUM, 0);

    EXPECT_EQ(buf_id, 1);

    Buffer buf_id_2 = mgr.ReadBuffer(rel, ForkNumber::MAIN_FORKNUM, 1);
    EXPECT_EQ(buf_id_2, 2);

    mgr.ReleaseBuffer(buf_id);
    mgr.ReleaseBuffer(buf_id);
    mgr.ReleaseBuffer(buf_id_2);
    delete rel;
}

TEST(hash_buff_mgr, p_new)
{
    BufferMgr mgr{};
    Relation rel = new RelationData;
    rel->rnode = 2;
    rel->oid = 2;

    Buffer buf_id = mgr.ReadBuffer(rel, ForkNumber::MAIN_FORKNUM, P_NEW);
    Buffer buf_id2 = mgr.ReadBuffer(rel, ForkNumber::MAIN_FORKNUM, P_NEW);

    EXPECT_EQ(buf_id, 1);
    EXPECT_EQ(buf_id2, 2);

    mgr.ReleaseBuffer(buf_id);
    mgr.ReleaseBuffer(buf_id2);

    delete rel;
}