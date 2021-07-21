#ifndef _itemptr_hpp_
#define _itemptr_hpp_

struct ItemPointerData {
    int ip_blkno;
    int ip_offset;
};

typedef ItemPointerData* ItemPointer;

#endif