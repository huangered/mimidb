#ifndef _buf_internal_hpp_
#define _buf_internal_hpp_

#include "mimi.h"
#include "access/relcache.h"
#include "storage/block.h"
#include "storage/page.h"
#include "storage/buf.h"
#include "util/hashmap.h"

typedef struct buftag {
    RelFileNode rnode;
    ForkNumber forkNum;
    BlockNumber blockNum;

    int
    hash() const {
        return rnode.relNode * 17 * 17 + forkNum * 17 + blockNum;
    }

    friend bool
    operator==(const buftag& l, const buftag& r) {
        return l.rnode == r.rnode && l.forkNum == r.forkNum && l.blockNum == r.blockNum;
    }

    friend bool
    operator!=(const buftag& l, const buftag& r) {
        return !(l == r);
    }

} BufferTag;

#define BUFFERTAG_EQUAL(a, b) ((a).rnode == (b).rnode && (a).forkNum == (b).forkNum && (a).blockNum == (b).blockNum)

struct BufferDesc {
    BufferTag tag;
    int buf_id;
    // the buf state, include ref_count;
    int refcnt;
    // the buf is updated.
    bool dirty;
    int freeNext;
};

typedef union BufferDescPadded {
    BufferDesc bufferdesc;
} BufferDescPadded;

#define GetBufferDescriptor(id)          (&BufferDescriptors[(id)].bufferdesc)
#define BufferDescriptorGetBuffer(bdesc) ((bdesc)->buf_id + 1)

extern BufferDescPadded* BufferDescriptors;

/* buf freelist.cpp */
extern void StrategyInit();
extern BufferDesc* FindFreeBuffer();

#endif
