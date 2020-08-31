#include "storage/freespace.h"
#include "storage/bufmgr.h"
#include "storage/fsm_internal.h"
#include "storage/page.h"


BlockNumber GetPageWithFreeSpace(Relation rel, Size spaceNeeded) {
    Buffer buf;
    BlockNumber block;

    block = fsm_search_avail(rel, spaceNeeded);

    return block;
}

void RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace) {
    Buffer buf;
    FSMAddress addr;
    buf = fsm_readbuf(rel, addr);

    fsm_set_value(buf, usedBlock, freeSpace);

}
