#include "storage/freespace.h"
#include "storage/indexfsm.h"

BlockNumber
GetFreeIndexPage(Relation rel) {

    BlockNumber blkno = GetPageWithFreeSpace(rel, BLKSZ / 2);

    if (blkno != INVALID_BLOCK) {
        RecordUsedIndexPage(rel, blkno);
    }

    return blkno;
}

void
RecordFreeIndexPage(Relation rel, BlockNumber usedBlock) {
    RecordPageWithFreeSpace(rel, usedBlock, BLKSZ - 1);
}

void
RecordUsedIndexPage(Relation rel, BlockNumber usedBlock) {
    RecordPageWithFreeSpace(rel, usedBlock, 0);
}

void
IndexFreeSpaceMapVacuum(Relation rel) {
    FreeSpaceMapVacuum(rel);
}