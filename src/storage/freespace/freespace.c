#include "storage/freespace.h"
#include "storage/bufmgr.h"
#include "storage/fsm_internal.h"
#include "storage/page.h"

BlockNum GetPageWithFreeSpace(Relation rel, Size spaceNeeded) {
    BlockNum block;

    block = fsm_search_avail(rel, spaceNeeded);

    return block;
}

void RecordPageWithFreeSpace(Relation rel, BlockNum usedBlock, Size freeSpace) {
    fsm_set_value(rel, usedBlock, freeSpace);
}
