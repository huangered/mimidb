#ifndef _buf_internals_h_
#define _buf_internals_h_

#include "storage/block.h"
#include "access/rel.h"
#include "access/relpath.h"

typedef struct BufTag {
    RelFileNode rnode;
    ForkNumber forkNum;
    BlockNumber blockNum;
} BufferTag;

typedef struct BuffDesc {
    BufferTag tag;
    int buf_id;

    // the buf state, include ref_count;
    volatile int state;
    // the buf is updated.
    volatile bool dirty;
    int freeNext;
} BufferDesc;

#define INIT_BUFFERTAG(a, xx_rnode, xx_forknum, xx_blocknum) \
( \
    (a).rnode = (xx_rnode->rnode),\
    (a).forkNum = (xx_forknum),\
    (a).blockNum = (xx_blocknum) \
)

/* freelist.c */
extern void StrategyInitialize();
extern Buffer StrategyGetBuffer();
extern void StrategyFreeBuffer(Buffer buffer);

// private method
static inline uint32 buftag_hash(const void* key, Size keysize) {
    BufferTag* btag = (BufferTag*)key;
    return btag->rnode.relnode;
}
static inline bool buftag_equal(const void* left, const void* right, Size keysize) {
    int ret = memcmp(left, right, keysize);
    return ret == 0;
}

#endif // !_buf_internals_h_
