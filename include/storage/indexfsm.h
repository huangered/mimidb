#ifndef _index_fsm_h_
#define _index_fsm_h_

#include "storage/block.h"
#include "access/rel.h"

BlockNum GetFreeIndexPage(Relation rel);
void RecordUsedIndexPage(Relation rel, BlockNum usedBlock);

#endif // !_index_fsm_h_
