#include "storage/indexfsm.hpp"
#include "storage/freespace.hpp"
#include "storage/page.hpp"

BlockNumber GetFreeIndexPage(Relation rel) {

    BlockNumber blkno = freespace::GetPageWithFreeSpace(rel, BLKSZ / 2);

    if (blkno != INVALID_BLOCK) {
        RecordUsedIndexPage(rel, blkno);
    }

    return blkno;
}

void RecordUsedIndexPage(Relation rel, BlockNumber usedBlock) {
    freespace::RecordPageWithFreeSpace(rel, usedBlock, 0);
}
