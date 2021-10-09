#include "storage/freespace.hpp"
#include "storage/fsm_internal.hpp"
#include "storage/page.hpp"

static fsm* _fsm = new fsm{};

#define FSM_CATAGORIES 256
#define FSM_CAT_STEP   (BLKSZ / FSM_CATAGORIES)

static uint8 fsm_space_avail_to_cat(Size avail);
static Size fsm_space_cat_to_avail(uint8 cat);

BlockNumber
GetPageWithFreeSpace(Relation rel, Size spaceNeeded) {
    int min_cat = fsm_space_avail_to_cat(spaceNeeded);

    return _fsm->fsm_search(rel, spaceNeeded);
}

void
RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace) {
    int new_cat = fsm_space_avail_to_cat(freeSpace);
    FSMAddress addr;
    int slot = 0;

    addr = _fsm->fsm_get_location(usedBlock, &slot);
    _fsm->fsm_set_and_search(rel, addr, slot, new_cat, 0);
}

BlockNumber
RecordAndGetPageWithFreeSpace(Relation rel, BlockNumber oldPage, Size oldSpaceAvail, Size spaceNeeded) {
    uint old_cat   = fsm_space_avail_to_cat(oldSpaceAvail);
    uint space_cat = fsm_space_avail_to_cat(spaceNeeded);
    RecordPageWithFreeSpace(rel, oldPage, old_cat);
    return GetPageWithFreeSpace(rel, space_cat);
}

void
FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end) {
    if (end > start) {
        _fsm->fsm_vacuum_page(rel, FSM_ROOT_ADDRESS, start, end);
    }
}

void
FreeSpaceMapVacuum(Relation rel) {
}

/** private api **/
static uint8
fsm_space_avail_to_cat(Size avail) {
    int cat;

    cat = avail / FSM_CAT_STEP;

    if (cat > 254) {
        cat = 254;
    }
    return (uint8)cat;
}

static Size
fsm_space_cat_to_avail(uint8 cat) {
    return cat * FSM_CAT_STEP;
}
