#ifndef _itemptr_hpp_
#define _itemptr_hpp_

#include "storage/block.h"
#include "access/offset.h"

typedef struct ItemPointerData {
    BlockNumber ip_blkno;
    OffsetNumber ip_offset;
} ItemPointerData;

typedef ItemPointerData* ItemPointer;

#define ItemPointerGetBlockNumber(pointer)  (&(pointer)->ip_blkno)
#define ItemPointerGetOffsetNumber(pointer) (&(pointer)->ip_offset)

#endif
