#ifndef _freespace_h_
#define _freespace_h_

#include "storage/block.h"
#include "access/rel.h"

BlockNum GetPageWithFreeSpace(Relation rel, Size spaceNeeded);

#endif // !_freespace_h_
