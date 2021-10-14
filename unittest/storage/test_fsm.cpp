#include "../g.hpp"

#include "storage/freespace.hpp"

TEST(fsm, test_record) {
    Relation rel = new RelationData{};
    rel->rd_id   = FSM_REL_ID;
    rel->rd_node = { DB_ID, rel->rd_id };
    rel->rd_smgr = nullptr;

    RecordPageWithFreeSpace(rel, 0, 10);
    RecordPageWithFreeSpace(rel, 1, 1000);

    FreeSpaceMapVacuum(rel);

    BlockNumber blk = GetPageWithFreeSpace(rel, 100);

    EXPECT_EQ(blk, 1);
}
