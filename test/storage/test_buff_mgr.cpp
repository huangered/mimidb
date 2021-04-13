#include "../g.hpp"

#include "access/rel.hpp"
#include "storage/bufmgr.hpp"

#include "access/heap.hpp"

// test the basic usage in buff mgr.
TEST(buff_mgr, basic)
{
    BufferReset();
    Relation rel = new RelationData{};
    rel->rd_id = 1;
    rel->rd_node = { 1,2 };
    rel->rd_smgr = nullptr;
    for (int i{}; i < 10; i++) {
        Buffer buf_id = ReadBuffer(rel, i);
        EXPECT_GT(buf_id, 0);
    }
    delete rel;
}


TEST(buff_mgr, p_new)
{
    BufferReset();
    Relation rel = new RelationData{};
    rel->rd_id = 2;
    rel->rd_node = { 2, rel->rd_id };
    rel->rd_smgr = nullptr;

    Buffer buf_id = ReadBuffer(rel, P_NEW);
    //Buffer buf_id2 = ReadBuffer(rel, P_NEW);

    EXPECT_GT(buf_id, 0);
    //EXPECT_GT(buf_id2, 0);

    ReleaseBuffer(buf_id);
    //ReleaseBuffer(buf_id2);

    delete rel;
}


