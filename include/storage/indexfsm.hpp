#ifndef _index_fsm_h_
#define _index_fsm_h_

#include "storage/block.hpp"
#include "access/rel.hpp"

// find a free index page
BlockNumber GetFreeIndexPage(Relation rel);
void RecordUsedIndexPage(Relation rel, BlockNumber usedBlock);

#endif // !_index_fsm_h_
