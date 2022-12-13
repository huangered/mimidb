#include "storage/bufmgr.h"

typedef struct BufferStrategyControl {
    int firstFreeBuffer;
    int lastFreeBuffer;
} BufferStrategyControl;

static BufferStrategyControl* StrategyControl = NULL;

void
StrategyInit() {
    StrategyControl                  = (BufferStrategyControl*)palloc(sizeof(BufferStrategyControl));
    StrategyControl->firstFreeBuffer = 0;
    StrategyControl->lastFreeBuffer  = NBuffers - 1;
}

struct BufferDesc*
FindFreeBuffer() {
    struct BufferDesc* buf;
    if (StrategyControl->firstFreeBuffer >= 0) {
        buf                              = GetBufferDescriptor(StrategyControl->firstFreeBuffer);
        StrategyControl->firstFreeBuffer = buf->freeNext;
        buf->freeNext                    = -1;

        return buf;
    }

    printf("not find free buffer\n");

    return NULL;
}
