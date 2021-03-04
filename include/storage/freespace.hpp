#ifndef _freespace_h_
#define _freespace_h_

#include "storage/block.hpp"
#include "access/rel.hpp"

class freespace {
public:
	/*
	find a page with available free space
	*/
	static BlockNumber GetPageWithFreeSpace(Relation rel, Size spaceNeeded);
	static void RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace);
	static void FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end);
};

#endif // !_freespace_h_
