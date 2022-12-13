#ifndef _itemptr_hpp_
#define _itemptr_hpp_

#include "storage/block.h"
#include "access/offset.h"

struct ItemPointerData {
    BlockNumber ip_blkno;
    OffsetNumber ip_offset;
};

typedef struct ItemPointerData* ItemPointer;

#define ItemPointerGetBlockNumber(pointer)  (&(pointer)->ip_blkno)
#define ItemPointerGetOffsetNumber(pointer) (&(pointer)->ip_offset)

#endif
