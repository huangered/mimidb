#include "../g.hpp"

#include "access/rel.hpp"
#include "storage/bufmgr.hpp"

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