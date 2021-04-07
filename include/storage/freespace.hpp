#ifndef _freespace_h_
#define _freespace_h_

#include "storage/block.hpp"
#include "access/rel.hpp"
#include "storage/fsm_internal.hpp"

// 堆表
BlockNumber GetPageWithFreeSpace(Relation rel, Size spaceNeeded);
void RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace);
void FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end);
BlockNumber RecordAndGetPageWithFreeSpace(Relation rel, BlockNumber oldPage, Size oldSpaceAvail, Size spaceNeeded);

// 索引
BlockNumber GetFreeIndexPage(Relation rel);
void RecordUsedIndexPage(Relation rel, BlockNumber usedBlock);

#endif // !_freespace_h_
