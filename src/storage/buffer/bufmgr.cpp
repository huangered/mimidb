#include "storage/bufmgr.hpp"
#include "storage/buf_internals.hpp"
#include "port/shmem.hpp"
#include "util/mctx.hpp"
#include "util/hash.hpp"
#include "storage/fd.hpp"
#include "storage/smgr.hpp"

#define BLKSZ 8192
#define NBuffer 20

BufferMgr::BufferMgr() {
    size_t size = NBuffer * BLKSZ;
    _blocks = new char[size];
    memset(_blocks, 0, size);

    _buffDesc = new BufferDesc[NBuffer];

    for (int i{}; i < NBuffer; i++) {
        _buffDesc[i].buf_id = i + 1;
        _buffDesc[i].freeNext = i + 2;
    }
    
    _buffDesc[NBuffer - 1].freeNext = 0;
    _freeBuffDesc = _buffDesc;
    _hashMap = new HashMap<BufferTag, Buffer>;
}

BufferMgr::~BufferMgr() {
    delete[] _blocks;
    delete[] _buffDesc;
    delete _hashMap;
}

Buffer
BufferMgr::ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    return BufferAlloc(rel, forkNumber, blkno)->buf_id;
}

BufferDesc*
BufferMgr::BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    Buffer buf_id = INVALID_BUFFER;
    BufferTag tag{ rel->oid, forkNumber, blkno };

    // use buftag to find
    bool result = _hashMap->Get(tag, &buf_id);
    
    if (buf_id > INVALID_BUFFER) {
        // add ref count;
        GetBufferDesc(buf_id)->state += 1;
        return GetBufferDesc(buf_id);
    }
    // if find, return
    // create new one and find a valid buffdesc or find a victim;

    buf_id = findFreeBuffer();
    // load page data into page ptr;
    //load_page(tag, buf_id);

    GetBufferDesc(buf_id)->state += 1;
    GetBufferDesc(buf_id)->tag = tag;
    // insert into hash
    _hashMap->Put(tag, buf_id);

    return GetBufferDesc(buf_id);
}

void
BufferMgr::ReleaseBuffer(Buffer buffer) {
    BufferDesc* bd = GetBufferDesc(buffer);
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
    char* data = new char[BLKSZ];
    memset(data, 0, BLKSZ);
    file_read(f, tag.blockNum, data);
    // read block;
    char* pagePtr = GetPage(buf + 1);

    memcpy(pagePtr, data, BLKSZ);
    delete[] path;
    delete[] data;
    file_close(f);
}

Page
BufferMgr::GetPage(Buffer bufId) {
    int index = (bufId - 1) * BLKSZ;
    char* p = _blocks + index;
    return p;
}

BufferDesc*
BufferMgr::GetBufferDesc(Buffer bufId) {
    BufferDesc* bd = &_buffDesc[bufId - 1];
    return bd;
}


Buffer
BufferMgr::findFreeBuffer() {
    BufferDesc* bd = _freeBuffDesc;
    _freeBuffDesc = &_buffDesc[_freeBuffDesc->freeNext - 1];
    bd->freeNext = 0;
    return bd->buf_id;
}
