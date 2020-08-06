#include "storage/indexfsm.h"
#include "storage/freespace.h"
#include "storage/page.h"

BlockNum GetFreeIndexPage(Relation rel) {

    BlockNum blkno = GetPageWithFreeSpace(rel, BLKSZ / 2);

    if (blkno != INVALID_BLOCK) {
        RecordUsedIndexPage(rel, blkno);
    }

    return blkno;
}

void RecordUsedIndexPage(Relation rel, BlockNum usedBlock) {
    RecordPageWithFreeSpace(rel, usedBlock, 0);
}
