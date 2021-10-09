#include "../g.hpp"

#include "storage/bufmgr.hpp"
#include "storage/fsm_internal.hpp"
#include "storage/freespace.hpp"
#include "storage/smgr.hpp"

TEST(fsm, print) {
    printf("%d\n%d\n%d\n", NodesPerPage, NonLeafNodesPerPage, LeafNodesPerPage);
}

TEST(fsm, leaf) {
    Relation rel = new RelationData{};
    rel->rd_id   = 2000;
    rel->rd_node = { 2000, rel->rd_id };
    rel->rd_smgr = nullptr;

    RecordPageWithFreeSpace(rel, 0, BLKSZ);
    FreeSpaceMapVacuumRange(rel, 0, 1);
    GetPageWithFreeSpace(rel, 20);
}
