#ifndef _buf_internals_h_
#define _buf_internals_h_

#include "storage/block.hpp"
#include "access/rel.hpp"
#include "access/relpath.hpp"

struct BufferTag {
    int rnode;
    ForkNumber forkNum;
    BlockNumber blockNum;

    int hash() const {
        return rnode * 17 * 17 + forkNum * 17 + blockNum;
    }

    friend bool operator==(const BufferTag& l, const BufferTag& r) {
        return l.rnode == r.rnode && l.forkNum == r.forkNum && l.blockNum == r.blockNum;
    }

    friend bool operator!=(const BufferTag& l, const BufferTag& r) {
        return !(l == r);
    }
};

struct BufferDesc {
    BufferTag tag;
    int buf_id;

    // the buf state, include ref_count;
    volatile int state;
    // the buf is updated.
    volatile bool dirty;
    int freeNext;
};

/* freelist.c */
extern void StrategyInitialize();
extern Buffer StrategyGetBuffer();
extern void StrategyFreeBuffer(Buffer buffer);

#endif // !_buf_internals_h_
