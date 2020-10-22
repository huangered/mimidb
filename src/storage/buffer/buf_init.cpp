#include "storage/bufmgr.hpp"
#include "storage/buf_internals.hpp"
#include "port/shmem.hpp"
#include "util/mctx.hpp"
#include "util/hash.hpp"
#include "storage/fd.hpp"

char* BufferBlocks = NULL;
BufferDesc* BuffDesc = NULL;
BufferDesc* freeBuffDesc;
Hash* bufHash;

void BufferInit() {
    Size size = (Size)NBuffers * BLKSZ;
    // will use shmem_init in the future
    BufferBlocks = (char*)palloc(size);
    memset(BufferBlocks, 0, size);
    // will use shmem_init in the future
    BuffDesc = (BufferDesc*)palloc(NBuffers * sizeof(BufferDesc));
    memset(BuffDesc, 0, NBuffers * sizeof(BufferDesc));

    for (int i = 0; i < NBuffers; i++) {
        BuffDesc[i].buf_id = i;
        BuffDesc[i].freeNext = i + 1;
        BuffDesc[i].state = 0;
    }
    BuffDesc[NBuffers - 1].freeNext = -1;
    freeBuffDesc = BuffDesc;
    bufHash = hash_create("local_buf", buftag_hash, buftag_equal, sizeof(BufferTag), sizeof(BufferDesc));

    StrategyInitialize();
}