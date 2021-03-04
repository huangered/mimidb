#include "storage/bufmgr.hpp"
#include "storage/buf_internals.hpp"
#include "port/shmem.hpp"
#include "util/mctx.hpp"
#include "util/hash.hpp"
#include "storage/fd.hpp"

char* BufferBlocks = NULL;
BufferDesc* BuffDesc = NULL;
BufferDesc* freeBuffDesc;
HashMap<BufferTag, BufferDesc> bufHash;

void BufferInit() {
    Size size = (Size)20 * BLKSZ;
    // will use shmem_init in the future
    BufferBlocks = (char*)palloc(size);
    memset(BufferBlocks, 0, size);
    // will use shmem_init in the future
    BuffDesc = (BufferDesc*)palloc(20 * sizeof(BufferDesc));
    memset(BuffDesc, 0, 20 * sizeof(BufferDesc));

    for (int i = 0; i < 20; i++) {
        BuffDesc[i].buf_id = i;
        BuffDesc[i].freeNext = i + 1;
        BuffDesc[i].state = 0;
    }
    BuffDesc[20 - 1].freeNext = -1;
    freeBuffDesc = BuffDesc;

    StrategyInitialize();
}