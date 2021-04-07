#include "storage/freespace.hpp"
#include "storage/bufmgr.hpp"
#include "storage/fsm_internal.hpp"
#include "storage/page.hpp"

fsm* _fsm;

BlockNumber 
GetPageWithFreeSpace(Relation rel, Size spaceNeeded) {
    BlockNumber block;

    block = _fsm->fsm_search(rel, spaceNeeded);

    return block;
}

void
RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace) {

    FSMAddress addr;
    int slot = 0;

    addr = _fsm->fsm_get_location(usedBlock, &slot);
    _fsm->fsm_set_and_search(rel, addr, slot, freeSpace, 0);

}

BlockNumber
RecordAndGetPageWithFreeSpace(Relation rel, BlockNumber oldPage, Size oldSpaceAvail, Size spaceNeeded) {
    RecordPageWithFreeSpace(rel, oldPage, oldSpaceAvail);
    return GetPageWithFreeSpace(rel, spaceNeeded);
}


void
FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end) {
    if (end > start) {
        _fsm->fsm_vacuum_page(rel, FSM_ROOT_ADDRESS, start, end);
    }
}

