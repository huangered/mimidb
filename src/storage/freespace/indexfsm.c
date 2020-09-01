#include "storage/indexfsm.h"
#include "storage/freespace.h"
#include "storage/page.h"

BlockNumber GetFreeIndexPage(Relation rel) {

    BlockNumber blkno = GetPageWithFreeSpace(rel, BLKSZ / 2);

    if (blkno != INVALID_BLOCK) {
        RecordUsedIndexPage(rel, blkno);
    }

    return blkno;
}

void RecordUsedIndexPage(Relation rel, BlockNumber usedBlock) {
    RecordPageWithFreeSpace(rel, usedBlock, 0);
}
