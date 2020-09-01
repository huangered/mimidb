#include "storage/freespace.h"
#include "storage/bufmgr.h"
#include "storage/fsm_internal.h"
#include "storage/page.h"


BlockNumber GetPageWithFreeSpace(Relation rel, Size spaceNeeded) {
    BlockNumber block;

    block = fsm_search(rel, spaceNeeded);

    return block;
}

void RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace) {

    FSMAddress addr;
    int slot = 0;

    addr = fsm_get_location(usedBlock, &slot);
    fsm_set_and_search(rel, addr, slot, freeSpace, 0);

}

void FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end) {
    if (end > start) {
        fsm_vacuum_page(rel, FSM_ROOT_ADDRESS, start, end);
    }
}
