#include "storage/bufmgr.hpp"

char* BufferBlocks;
BufferDescPadded* BufferDescriptors;

int NBuffers = 1024;

/*
 * init the shared buffer pool
 */
void
InitBufferPool(void) {
    size_t size  = NBuffers * BLKSZ;
    BufferBlocks = (char*)std::malloc(size);

    memset(BufferBlocks, 0, size);

    BufferDescriptors = (BufferDescPadded*)std::malloc(NBuffers * sizeof(BufferDescPadded));

    memset(BufferDescriptors, 0, NBuffers * sizeof(BufferDescPadded));

    for (int i{ 0 }; i < NBuffers; i++) {
        BufferDesc* desc = GetBufferDescriptor(i);
        desc->buf_id     = i;
        desc->freeNext   = i + 1;
    }

    GetBufferDescriptor(NBuffers - 1)->freeNext = INVALID_BUFFER;
}
