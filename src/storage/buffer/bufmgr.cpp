#include "access/rel.hpp"
#include "storage/bufmgr.hpp"
#include "storage/smgr.hpp"

#define NBuffer 20
#define P_NEW INVALID_BLOCK

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
BufferMgr::ReadBuffer(Relation rel, BlockNumber blkno) {
    return ReadBufferExtend(rel, MAIN_FORKNUM, blkno);
}

Buffer
BufferMgr::ReadBufferExtend(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    RelationOpenSmgr(rel, smgropen(rel, forkNumber));

    return ReadBuffer_common(rel, forkNumber, blkno);
}

/*
*/
Buffer
BufferMgr::ReadBuffer_common(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    BufferDesc* desc;
    bool isExtend{};

    if (blkno == P_NEW) {
        isExtend = true;
    }

    if (isExtend) {
        blkno = smgrblocks(rel, forkNumber);
    }

    desc = _BufferAlloc(rel, forkNumber, blkno);

    Page page = GetPage(desc->buf_id);
    // load or save data
    if (isExtend) {
        memset(page, 0, BLKSZ);
        smgrextend(rel, page, blkno, forkNumber);
    }
    else {
        smgrread(rel, forkNumber, blkno, page);
    }    

    return desc->buf_id;
}

BufferDesc*
BufferMgr::_BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    Buffer buf_id = INVALID_BUFFER;
    BufferTag tag{ rel->rd_id, forkNumber, blkno };

    // use buftag to find
    bool result = _hashMap->Get(tag, &buf_id);
    
    if (buf_id > INVALID_BUFFER) {
        // add ref count;
        GetBufferDesc(buf_id)->state += 1;
        return GetBufferDesc(buf_id);
    }
    // if find, return
    // create new one and find a valid buffdesc or find a victim;

    buf_id = _FindFreeBuffer();

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
BufferMgr::_FindFreeBuffer() {
    BufferDesc* bd = _freeBuffDesc;
    _freeBuffDesc = &_buffDesc[_freeBuffDesc->freeNext - 1];
    bd->freeNext = 0;
    return bd->buf_id;
}
