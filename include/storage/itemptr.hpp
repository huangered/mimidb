#ifndef _itemptr_hpp_
#define _itemptr_hpp_

#include "storage/block.hpp"
#include "access/offset.hpp"

struct ItemPointerData {
    BlockNumber ip_blkno;
    OffsetNumber ip_offset;
};

typedef ItemPointerData* ItemPointer;

#define ItemPointerGetBlockNumber(pointer)  (&(pointer)->ip_blkno)
#define ItemPointerGetOffsetNumber(pointer) (&(pointer)->ip_offset)

#endif
