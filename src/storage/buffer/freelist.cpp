#include "storage/bufmgr.hpp"
#include "storage/buf_internals.hpp"
#include "storage/spin.hpp"
#include "util/mctx.hpp"

BufferMgr _bufMgr;

typedef struct BufferStrategyControl {
    slock_t lock;

    int firstFreeBuffer;
    int lastFreeBuffer;

    int numBufferAllocs;
}BufferStrategyControl;

static BufferStrategyControl* StrategyControl;

/*
get a free buffer from list
*/
Buffer
StrategyGetBuffer() {
    //while (true) {
    //    if (freeBuffDesc != NULL) {
    //        BufferDesc* bd = freeBuffDesc;
    //        freeBuffDesc = BuffDesc + freeBuffDesc->freeNext;
    //        bd->freeNext = -1;
    //        
    //        return bd->buf_id;
    //    }
    //    else {
    //        // find victim to free 
    //    }
    //}
    return 0;
}

/*
release the buffer to list
*/
void
StrategyFreeBuffer(Buffer buffer) {
    SpinLockAcquire(&StrategyControl->lock);

    BufferDesc bd = _bufMgr.GetBufferDesc(buffer);
    //bd.freeNext = freeBuffDesc->buf_id;
    //freeBuffDesc = bd;

    SpinLockRelease(&StrategyControl->lock);
}

void
StrategyInitialize() {
    StrategyControl = (BufferStrategyControl*)palloc(sizeof(BufferStrategyControl));

    SpinLockInit(&StrategyControl->lock);

    StrategyControl->firstFreeBuffer = 0;
    //StrategyControl->lastFreeBuffer = NBuffers - 1;

    StrategyControl->numBufferAllocs = 0;
}