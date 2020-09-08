#include "storage/bufmgr.h"
#include "storage/buf_internals.h"
#include "port/shmem.h"
#include "util/mctx.h"
#include "util/hash.h"
#include "storage/fd.h"

char* BufferBlocks = NULL;
BufferDesc* BuffDesc = NULL;
BufferDesc* freeBuffDesc;
Hash* bufHash;

void BufferInit() {
    Size size = (Size)NBuffer * BLKSZ;
    // will use shmem_init in the future
    BufferBlocks = palloc(size);
    memset(BufferBlocks, 0, size);
    // will use shmem_init in the future
    BuffDesc = palloc(NBuffer * sizeof(BufferDesc));
    memset(BuffDesc, 0, NBuffer * sizeof(BufferDesc));

    for (int i = 0; i < NBuffer; i++) {
        BuffDesc[i].buf_id = i;
        BuffDesc[i].freeNext = i + 1;
        BuffDesc[i].state = 0;
    }
    BuffDesc[NBuffer - 1].freeNext = -1;
    freeBuffDesc = BuffDesc;
    bufHash = hash_create("local_buf", buftag_hash, buftag_equal, sizeof(BufferTag), sizeof(BufferDesc));
}