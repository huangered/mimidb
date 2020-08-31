#include "storage/fsm_internal.h"

static Buffer fsm_readbuf(Relation rel);

/*
1. find a available block
2. if no block find , fsm_extend new page and search again
*/
BlockNum fsm_search_avail(Relation rel, Size spaceNeed) {
    Buffer buf;

    buf = fsm_readbuf(rel);
    Page page = BufferGetPage(buf);
    FSMPage fsm = (FSMPage)PageGetContent(page);

    for (int i = 1; i < 100; i++) {
        if (fsm->items[i] > spaceNeed) {
            return i;
        }
    }

    return INVALID_BLOCK;
}

void fsm_set_value(Relation rel, BlockNum usedBlock, Size freeSpace) {
    Buffer buf;

    buf = fsm_readbuf(rel); 
    Page page = BufferGetPage(buf);
    FSMPage fsm = (FSMPage)PageGetContent(page);
    fsm->items[usedBlock] = freeSpace;
}

Buffer fsm_readbuf(Relation rel) {
    // fsm block num is 0 now.
    Buffer buf = ReadBuffer(rel, FSM_FORKNUM, 0);

    if (PageIsNew(BufferGetPage(buf))) {
        PageInit(BufferGetPage(buf), BLKSZ, 0);
    }

    return buf;
}

void
fsm_extend(Relation rel, BlockNum block) {

}