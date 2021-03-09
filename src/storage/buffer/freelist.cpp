#include "storage/bufmgr.hpp"
#include "storage/buf_internals.hpp"
#include "storage/spin.hpp"
#include "util/mctx.hpp"



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
BufferStrategy::GetBuffer() {
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
BufferStrategy::FreeBuffer(Buffer buffer) {
    SpinLockAcquire(&StrategyControl->lock);

    BufferDesc* bd = _bufMgr->GetBufferDesc(buffer);
    //bd.freeNext = freeBuffDesc->buf_id;
    //freeBuffDesc = bd;

    SpinLockRelease(&StrategyControl->lock);
}

