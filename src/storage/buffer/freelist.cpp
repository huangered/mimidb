#include "storage/bufmgr.hpp"

typedef struct BufferStrategyControl {
    int firstFreeBuffer;
    int lastFreeBuffer;
} BufferStrategyControl;

static BufferStrategyControl* StrategyControl = nullptr;

void
StrategyInit() {
    StrategyControl                  = (BufferStrategyControl*)std::malloc(sizeof(BufferStrategyControl));
    StrategyControl->firstFreeBuffer = 0;
    StrategyControl->lastFreeBuffer  = NBuffers - 1;
}

BufferDesc*
FindFreeBuffer() {
    BufferDesc* buf;
    if (StrategyControl->firstFreeBuffer >= 0) {
        buf                              = GetBufferDescriptor(StrategyControl->firstFreeBuffer);
        StrategyControl->firstFreeBuffer = buf->freeNext;
        buf->freeNext                    = -1;

        return buf;
    }

    printf("not find free buffer\n");

    return nullptr;
}
