#include "storage/bufmgr.h"
#include "storage/buf_internals.h"
#include "port/shmem.h"
#include "util/mctx.h"
#include "util/hash.h"
#include "storage/fd.h"

static BufferDesc* BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno);
static void load_page(BufferTag tag, Buffer buf);

Buffer
ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    return BufferAlloc(rel, forkNumber, blkno)->buf_id + 1;
}

BufferDesc*
BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    Buffer buf_id;
    BufferTag tag;
    INIT_BUFFERTAG(tag, rel, forkNumber, blkno);

    // use buftag to find
    void* result = hash_search(bufHash, Search, &tag);
    if (result == NULL) {
        buf_id = -1;
    }
    else {
        buf_id = *(Buffer*)result;
    }
    if (buf_id >= 0) {
        // add ref count;
        GetBufferDesc(buf_id)->state += 1;
        return GetBufferDesc(buf_id);
    }
    // if find, return
    // create new one and find a valid buffdesc or find a victim;
    while (true) {

        if (freeBuffDesc != NULL) {
            BufferDesc* bd = freeBuffDesc;
            freeBuffDesc = BuffDesc + freeBuffDesc->freeNext;
            bd->freeNext = -1;
            bd->tag = tag;
            buf_id = bd->buf_id;
            break;
        }
        else {
            // find victim to free 
        }
    }
    // load page data into page ptr;
    load_page(tag, buf_id);

    GetBufferDesc(buf_id)->state += 1;
    GetBufferDesc(buf_id)->tag = tag;
    // insert into hash
    Buffer* nBuf = (Buffer*)hash_search(bufHash, Add, &tag);
    *nBuf = buf_id;
    // return buf

    return GetBufferDesc(buf_id);
}

void ReleaseBuffer(Buffer buffer) {
    BufferDesc* bd = GetBufferDesc(buffer - 1);
    bd->state -= 1;
}


// easy implement
static void load_page(BufferTag tag, Buffer buf) {
    char* path = GetRelPath(tag.rnode, tag.forkNum);
    // read file
    fd* f = file_open(path);
    if (f->filePtr == NULL) {
        file_init(path);
        f = file_open(path);
    }
    char* data = palloc(BLKSZ);
    memset(data, 0, BLKSZ);
    file_read(f, tag.blockNum, data);
    // read block;
    char* pagePtr = BufferGetPage(buf + 1);

    memcpy(pagePtr, data, BLKSZ);
    pfree(path);
    pfree(data);
    file_close(f);
}
