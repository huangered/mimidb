#include "storage/bufmgr.h"

char* BufferBlocks;
BufferDescPadded* BufferDescriptors;

/*
 * init the shared buffer pool
 */
void
InitBufferPool(void) {
    size_t size  = NBuffers * BLKSZ;
    BufferBlocks = (char*)palloc(size);

    memset(BufferBlocks, 0, size);

    BufferDescriptors = (BufferDescPadded*)palloc(NBuffers * sizeof(BufferDescPadded));

    memset(BufferDescriptors, 0, NBuffers * sizeof(BufferDescPadded));

    for (int i=0; i < NBuffers; i++) {
       struct  BufferDesc* desc = GetBufferDescriptor(i);
        desc->buf_id     = i;
        desc->freeNext   = i + 1;
    }

    GetBufferDescriptor(NBuffers - 1)->freeNext = INVALID_BUFFER;

    StrategyInit();
}
