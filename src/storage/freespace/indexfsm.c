#include "storage/indexfsm.h"
#include "storage/freespace.h"

BlockNum GetFreeIndexPage(Relation rel) {

    BlockNum blkno = GetPageWithFreeSpace(rel, 8192 / 2);

    if (blkno != INVALID_BLOCK) {
        void RecordUsedIndexPage(rel, blkno);
    }

    return blkno;
}

void RecordUsedIndexPage(Relation rel, BlockNum usedBlock) {
    RecordPageWithFreeSpace(rel, usedBlock, 0);
}
