#ifndef _itemid_hpp_
#define _itemid_hpp_

struct ItemPointerData {
    int blocknum;
    int offset;
};

typedef ItemPointerData* ItemPointer;

#endif