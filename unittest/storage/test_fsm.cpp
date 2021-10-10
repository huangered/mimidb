#include "../g.hpp"

#include "storage/freespace.hpp"

TEST(fsm, test_record) {
    Relation rel = new RelationData{};
    rel->rd_id   = 2000;
    rel->rd_node = { 2000, rel->rd_id };
    rel->rd_smgr = nullptr;

    RecordPageWithFreeSpace(rel, 0, 1000);

    FreeSpaceMapVacuum(rel);

    BlockNumber blk = GetPageWithFreeSpace(rel, 100);

    EXPECT_EQ(blk, 0);
}
