#include "storage/fsm_internal.h"

BlockNum fsm_search_avail(Buffer buf, Size spaceNeed) {
    Page page = BufferGetPage(buf);
    FSMPage fsm = (FSMPage)PageGetContent(page);

    for (int i = 1; i < 100; i++) {
        if (fsm->items[i] > spaceNeed) {
            return i;
        }
    }

    return INVALID_BLOCK;
}

void fsm_set_value(Buffer buf, BlockNum usedBlock, Size freeSpace) {
    Page page = BufferGetPage(buf);
    FSMPage fsm = (FSMPage)PageGetContent(page);
    fsm->items[usedBlock] = freeSpace;
}

void
fsm_extend() {

}