#include "storage/bufmgr.hpp"
#include "storage/buf_internals.hpp"
#include "port/shmem.hpp"
#include "util/mctx.hpp"
#include "util/hash.hpp"
#include "storage/fd.hpp"
#include "storage/smgr.hpp"


Buffer
BufferMgr::ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    return BufferAlloc(rel, forkNumber, blkno)->buf_id + 1;
}

BufferDesc*
BufferMgr::BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    Buffer buf_id;
    BufferTag tag{ rel->oid, forkNumber, blkno };

    // use buftag to find
    bool result = _hashMap->Get(tag, &buf_id);
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

    buf_id = StrategyGetBuffer();
    // load page data into page ptr;
    load_page(tag, buf_id);

    GetBufferDesc(buf_id)->state += 1;
    GetBufferDesc(buf_id)->tag = tag;
    // insert into hash
    _hashMap->Put(tag, buf_id);

    return GetBufferDesc(buf_id);
}

void
BufferMgr::ReleaseBuffer(Buffer buffer) {
    BufferDesc* bd = GetBufferDesc(buffer - 1);
    bd->state -= 1;
}

void
BufferMgr::FlushBuffer(BufferDesc* buffDesc) {

    char* buf = GetPage(buffDesc->buf_id);

    //smgrwrite(buffDesc->tag.rnode, buffDesc->tag.forkNum, buffDesc->tag.blockNum, buf);
}

// easy implement
void BufferMgr::load_page(BufferTag tag, Buffer buf) {
    char* path = GetRelPath(tag.rnode, tag.forkNum);
    // read file
    fd* f = file_open(path);
    if (f->filePtr == NULL) {
        file_init(path);
        f = file_open(path);
    }
    char* data = (char*)palloc(BLKSZ);
    memset(data, 0, BLKSZ);
    file_read(f, tag.blockNum, data);
    // read block;
    char* pagePtr = GetPage(buf + 1);

    memcpy(pagePtr, data, BLKSZ);
    pfree(path);
    pfree(data);
    file_close(f);
}
