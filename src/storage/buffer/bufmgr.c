#include "storage/bufmgr.h"
#include "storage/buf_internals.h"
#include "port/shmem.h"
#include "util/mctx.h"
#include "util/hash.h"

static int BufferSize = 16;
static BufferDesc* buffDesc;
static BufferDesc* freeBuffDesc;
static Hash* bufHash;

#define BufferDescById(buf_id)  (buffDesc + buf_id)

static uint32 buftag_hash(const void* key, Size keysize);
static bool buftag_equal(const void* left, const void* right, Size keysize);

void BufferInit() {
    Size size = (Size)BufferSize * BLKSZ;
    // will use shmem_init in the future
    page = palloc(size);

    buffDesc = palloc(BufferSize * sizeof(BufferDesc));

    for (int i = 0; i < BufferSize; i++) {
        buffDesc[i].buf_id = i;
        buffDesc[i].freeNext = i + 1;
        buffDesc[i].state = 0;
    }
    buffDesc[BufferSize - 1].freeNext = -1;

    bufHash = hash_create("local_buf", buftag_hash, buftag_equal, sizeof(BufferTag), sizeof(BufferDesc));
}

Buffer ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNum blkno) {
    Buffer buf_id;
    BufferTag tag;
    INIT_BUFFERTAG(tag, rel, forkNumber, blkno);

    // use buftag to find
    buf_id = *(Buffer*)hash_search(bufHash, Search, &tag);
    if (buf_id >= 0) {
        // add ref count;
        BufferDescById(buf_id)->state += 1;
        return buf_id;
    }
    // if find, return
    // create new one and find a valid buffdesc or find a victim;
    while (true) {

        if (freeBuffDesc != NULL) {
            BufferDesc* bd = freeBuffDesc;
            freeBuffDesc = buffDesc + freeBuffDesc->freeNext;
            bd->freeNext = -1;
            buf_id = bd->buf_id;
        }
        else {
            // find victim to free 
        }
    }

    BufferDescById(buf_id)->state += 1;
    BufferDescById(buf_id)->tag = tag;
    // insert into hash
    Buffer* nBuf = (Buffer*)hash_search(bufHash, Add, &tag);
    *nBuf = buf_id;
    // return buf

    return buf_id;
}

void ReleaseBuffer(Buffer buffer) {
    BufferDesc* bd = BufferDescById(buffer);
    bd->state -= 1;
    // remove it from hash if its ref 
    if (bd->state == 0) {
        bd->freeNext = freeBuffDesc->buf_id;
        freeBuffDesc = bd;
    }
}

// private method
static uint32 buftag_hash(const void* key, Size keysize) {
    BufferTag* btag = (BufferTag*)key;
    return btag->rnode;
}
static bool buftag_equal(const void* left, const void* right, Size keysize) {
    int ret = memcmp(left, right, keysize);
    return ret == 0;
}
