#ifndef _freespace_h_
#define _freespace_h_

#include "storage/block.h"
#include "access/rel.h"

/*
find a page with available free space
*/
BlockNum GetPageWithFreeSpace(Relation rel, Size spaceNeeded);
void RecordPageWithFreeSpace(Relation rel, BlockNum usedBlock, Size freeSpace);

#endif // !_freespace_h_
