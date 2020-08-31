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
    Buffer buf;
    FSMAddress addr;
    buf = fsm_readbuf(rel, addr, true);

    fsm_set_value(buf, usedBlock, freeSpace);

}
