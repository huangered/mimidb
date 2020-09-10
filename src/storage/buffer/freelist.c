#include "storage/bufmgr.h"
#include "storage/buf_internals.h"

/*
get a free buffer from list
*/
Buffer
StrategyGetBuffer() {
    while (true) {
        if (freeBuffDesc != NULL) {
            BufferDesc* bd = freeBuffDesc;
            freeBuffDesc = BuffDesc + freeBuffDesc->freeNext;
            bd->freeNext = -1;
            
            return bd->buf_id;
        }
        else {
            // find victim to free 
        }
    }
}

/*
release the buffer to list
*/
void
StrategyFreeBuffer(Buffer buffer) {

}
