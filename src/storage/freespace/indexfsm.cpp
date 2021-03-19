#include "storage/freespace.hpp"
#include "storage/page.hpp"

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
