#ifndef _itemptr_h_
#define _itemptr_h_

typedef struct ItemPointerData
{
	int ip_blkno;
	int ip_offset;
} ItemPointerData;

typedef ItemPointerData* ItemPointer;

#endif