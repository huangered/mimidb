#include "storage/freespace.hpp"
#include "storage/bufmgr.hpp"
#include "storage/fsm_internal.hpp"
#include "storage/page.hpp"


BlockNumber freespace::GetPageWithFreeSpace(Relation rel, Size spaceNeeded) {
    BlockNumber block;

    block = fsm_search(rel, spaceNeeded);

    return block;
}

void freespace::RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace) {

    FSMAddress addr;
    int slot = 0;

    addr = fsm_get_location(usedBlock, &slot);
    fsm_set_and_search(rel, addr, slot, freeSpace, 0);

}

void freespace::FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end) {
    if (end > start) {
        fsm_vacuum_page(rel, FSM_ROOT_ADDRESS, start, end);
    }
}
