#include "../g.hpp"

#include "access/rel.hpp"
#include "storage/bufmgr.hpp"
#include "access/heap.hpp"

// test the basic usage in buff mgr.
TEST(buff_mgr, p_new) {
    Relation rel = new RelationData{};
    rel->rd_id   = BUF_REL_ID;
    rel->rd_node = { DB_ID, rel->rd_id };
    rel->rd_smgr = nullptr;
    for (int i = 0; i < 10; i++) {
        Buffer buf_id = ReadBuffer(rel, P_NEW);
        EXPECT_GT(buf_id, 0);
        FlushBuffer(buf_id);
        ReleaseBuffer(buf_id);
    }
    delete rel;
}
