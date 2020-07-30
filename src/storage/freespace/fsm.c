#include "storage/fsm_internal.h"


BlockNum fsm_search_avail(Buffer buf, Size spaceNeed) {
    Page page = BufferGetPage(buf);
    FSMPage fsm = (FSMPage)PageGetContent(page);

    for (int i = 0; i < 100; i++) {
        if (fsm->items[i] > spaceNeed) {
            return fsm->items[i];
        }
    }

    return INVALID_BLOCK;
}

void fsm_set_value(Buffer buf, BlockNum usedBlock, Size freeSpace) {
    FSMPage fsm = (FSMPage)BufferGetBlock(buf);

    fsm->items[usedBlock] = freeSpace;
}