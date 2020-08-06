#include "storage/bufmgr.h"
#include "storage/buf_internals.h"
#include "port/shmem.h"
#include "util/mctx.h"
#include "util/hash.h"
#include "storage/fd.h"

#define NBuffer     16
char* BufferBlocks = NULL;
BufferDesc* buffDesc = NULL;
static BufferDesc* freeBuffDesc;
static Hash* bufHash;


static void load_page(BufferTag tag, Buffer buf);

void BufferInit() {
    Size size = (Size)NBuffer * BLKSZ;
    // will use shmem_init in the future
    BufferBlocks = palloc(size);
    memset(BufferBlocks, 0, size);
    // will use shmem_init in the future
    buffDesc = palloc(NBuffer * sizeof(BufferDesc));
    memset(buffDesc, 0, NBuffer * sizeof(BufferDesc));

    for (int i = 0; i < NBuffer; i++) {
        buffDesc[i].buf_id = i;
        buffDesc[i].freeNext = i + 1;
        buffDesc[i].state = 0;
    }
    buffDesc[NBuffer - 1].freeNext = -1;
    freeBuffDesc = buffDesc;
    bufHash = hash_create("local_buf", buftag_hash, buftag_equal, sizeof(BufferTag), sizeof(BufferDesc));
}

Buffer ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNum blkno) {
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
        return buf_id;
    }
    // if find, return
    // create new one and find a valid buffdesc or find a victim;
    while (true) {

        if (freeBuffDesc != NULL) {
            BufferDesc* bd = freeBuffDesc;
            freeBuffDesc = buffDesc + freeBuffDesc->freeNext;
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

    return buf_id;
}

void ReleaseBuffer(Buffer buffer) {
    BufferDesc* bd = GetBufferDesc(buffer);
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
    char* pagePtr = (BufferBlocks + buf * BLKSZ);

    memcpy(pagePtr, data, BLKSZ);
    pfree(path);
    pfree(data);
    file_close(f);
}
