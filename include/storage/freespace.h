#ifndef _freespace_h_
#define _freespace_h_

#include "storage/block.h"
#include "access/rel.h"

// 堆表
Size GetRecordedFreeSpace(Relation rel, BlockNumber heapBlk);
BlockNumber GetPageWithFreeSpace(Relation rel, Size spaceNeeded);
void RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace);
void FreeSpaceMapVacuum(Relation rel);
void FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end);
BlockNumber RecordAndGetPageWithFreeSpace(Relation rel, BlockNumber oldPage, Size oldSpaceAvail, Size spaceNeeded);
void UpdateFreeSpaceMap(Relation rel, BlockNumber startBlkNum, BlockNumber endBlkNum, Size freeSpace);

#endif // !_freespace_h_
