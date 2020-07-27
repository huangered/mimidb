#include "storage/freespace.h"
#include "storage/bufmgr.h"
#include "storage/fsm_internal.h"
#include "storage/page.h"

static Buffer fsm_readbuf(Relation rel);

BlockNum GetPageWithFreeSpace(Relation rel, Size spaceNeeded) {
    Buffer buf;
    BlockNum block;

    buf = fsm_readbuf(rel);

    block = fsm_search_avail(buf, spaceNeeded);

    return block;
}

void RecordPageWithFreeSpace(Relation rel, BlockNum usedBlock, Size freeSpace) {
    Buffer buf;

    buf = fsm_readbuf(rel);

    fsm_set_value(buf, usedBlock, freeSpace);
}

Buffer fsm_readbuf(Relation rel) {
    // fsm block num is 0 now.
    Buffer buf = ReadBuffer(rel, FSM_FORKNUM, 0);

    if (PageIsNew(BufferGetPage(buf))) {
        PageInit(BufferGetPage(buf), BLKSZ);
    }

    return buf;
}