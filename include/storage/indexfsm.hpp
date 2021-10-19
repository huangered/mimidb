#ifndef _indexfsm_h_
#define _indexfsm_h_

#include "storage/block.hpp"
#include "access/rel.hpp"

// 索引
BlockNumber GetFreeIndexPage(Relation rel);
void RecordFreeIndexPage(Relation rel, BlockNumber usedBlock);
void RecordUsedIndexPage(Relation rel, BlockNumber usedBlock);
void IndexFreeSpaceMapVacuum(Relation rel);
#endif // !_indexfsm_h_
