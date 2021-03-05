#ifndef _freespace_h_
#define _freespace_h_

#include "storage/block.hpp"
#include "access/rel.hpp"
#include "storage/fsm_internal.hpp"

class freespace {
private:
	fsm* _fsm;
public:
	/*
	find a page with available free space
	*/
	BlockNumber GetPageWithFreeSpace(Relation rel, Size spaceNeeded);
	void RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace);
	void FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end);
};

#endif // !_freespace_h_
