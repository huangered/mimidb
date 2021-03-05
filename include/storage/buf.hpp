#ifndef _buf_hpp_
#define _buf_hpp_

#include "access/relpath.hpp"
#include "storage/block.hpp"

/*
zero is invalid, the index of shared buffer is [1..NBuffers]
*/
typedef int Buffer;

#define INVALID_BUFFER          0
#define BufferIsInvalid(buf)    ((buf) == INVALID_BUFFER)
#define BufferIsValid(buf)      ((buf) != INVALID_BUFFER)

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

#endif // !_BUFMGR_H_
