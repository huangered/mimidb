#ifndef _buf_internals_h_
#define _buf_internals_h_

#include "storage/block.h"
#include "access/rel.h"

typedef struct BufTag {
    int rnode;
    ForkNumber forkNum;
    BlockNum blockNum;
} BufferTag;

typedef struct BuffDesc {
    BufferTag tag;
    int buf_id;

    // the buf state, include ref_count;
    volatile int state;

    int freeNext;
} BufferDesc;

#define INIT_BUFFERTAG(a, xx_rnode, xx_forknum, xx_blocknum) \
( \
    (a).rnode = (xx_rnode),\
    (a).forkNum = (xx_forknum),\
    (a).blockNum = (xx_blocknum) \
)

#endif // !_buf_internals_h_
