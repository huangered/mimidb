#include "storage/bufmgr.h"
#include "storage/buf_internals.h"
#include "port/shmem.h"
#include "util/mctx.h"

static int BufferSize = 16;
static BufferDesc* buffDesc;


void BufferInit() {
    Size size = BufferSize * BLKSZ;
    page = shmem_init(size);

    buffDesc = palloc(BufferSize * sizeof(BufferDesc));

    for (int i = 0; i < BufferSize; i++) {
        buffDesc[i].bu_id = i;
        buffDesc[i].freeNext = i + 1;
    }
    buffDesc[BufferSize - 1].freeNext = 0;
}

Buffer ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNum blkno) {
    BufferTag tag;

    INIT_BUFFERTAG(tag, rel, forkNumber, blkno);



    return 0;
}

void ReleaseBuffer(Buffer buffer) {
}
