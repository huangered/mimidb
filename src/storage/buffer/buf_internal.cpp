#include "access/rel.hpp"
#include "storage/buf_internal.hpp"
#include "storage/smgr.hpp"
#include "storage/bufmgr.hpp"

#define NBuffer 32

BufferMgr::BufferMgr() {
    size_t size = NBuffer * BLKSZ;
    _blocks = new char[size];
    memset(_blocks, 0, size);

    _buffDesc = new BufferDesc[NBuffer]{};

    for (int i{}; i < NBuffer; i++) {
        BufferDesc* desc = &_buffDesc[i];
        desc->buf_id = i + 1;
        desc->freeNext = i + 2;
        printf("desc address %p\r\n", desc);
    }
    
    _buffDesc[NBuffer - 1].freeNext = 0;
    _freeBuffDesc = _buffDesc;
        index = 0;
}

BufferMgr::~BufferMgr() {
  printf("release buffmgr~~");
    delete[] _blocks;
    delete[] _buffDesc;
}

Buffer
BufferMgr::ReadBuffer(Relation rel, BlockNumber blkno) {
    return ReadBufferExtend(rel, MAIN_FORKNUM, blkno);
}

Buffer
BufferMgr::ReadBufferExtend(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    RelationOpenSmgr(rel);

    return _ReadBufferCommon(rel, forkNumber, blkno);
}

/*
*/
Buffer
BufferMgr::_ReadBufferCommon(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    BufferDesc* desc;
    bool found{};
    bool isExtend{};

    if (blkno == P_NEW) {
        isExtend = true;
    }

    if (isExtend) {
        blkno = smgr->Nblocks(rel->rd_smgr, forkNumber);
    }

    desc = _BufferAlloc(rel, forkNumber, blkno, &found);

    Page page = GetPage(desc->buf_id);

    if (found) {
        if (!isExtend) {
            return desc->buf_id;
        }
    }

    // load or save data
    if (isExtend) {
        memset(page, 0, BLKSZ);
        smgr->Extend(rel->rd_smgr, forkNumber, blkno, page);
    }
    else {
        smgr->Read(rel->rd_smgr, forkNumber, blkno, page);
    }    

    return desc->buf_id;
}

BufferDesc*
BufferMgr::_BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno, bool* found) {
    Buffer buf_id = INVALID_BUFFER;
    BufferTag tag{ rel->rd_id, forkNumber, blkno };

    // use buftag to find
    *found = _hashMap.Get(tag, &buf_id);

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
    _hashMap.Put(tag, buf_id);

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

    //smgr->Write(buffDesc->tag.rnode, buffDesc->tag.forkNum, buffDesc->tag.blockNum, buf);
}

Page
BufferMgr::GetPage(Buffer bufId) {
    int index1 = (bufId - 1) * BLKSZ;
    char* p = _blocks + index1;
    return p;
}

BufferDesc*
BufferMgr::GetBufferDesc(Buffer bufId) {
    BufferDesc* bd = &_buffDesc[bufId - 1];
    return bd;
}


Buffer
BufferMgr::_FindFreeBuffer() {
    static int i{ 0 };
    i++;
    printf("find free buffer %d\r\n", i);

    if(_freeBuffDesc == nullptr){
      printf("<<< exhausted\r\n");
      return 0;
    }
    
    for (int i{}; i < NBuffer; i++) {
        BufferDesc* desc = &_buffDesc[i];
        printf(">>>>>desc address %p , id %d, freenext %d\r\n", desc, desc->buf_id, desc->freeNext);
    }
    printf(">>>before index %d\r\n", index);
    printf(">>>before free desc address %p \r\n", _freeBuffDesc);
    printf(">>>before free desc address %p , id %d\r\n", _freeBuffDesc, _freeBuffDesc->buf_id);
    
    BufferDesc* bd = _freeBuffDesc;
    printf("bd exit %d\r\n", bd != nullptr);
    printf("require desc address %p\r\n", bd);
 
    printf("bd->buf id %d \r\n", bd->buf_id);
    printf("bd->freeNext %d\r\n", bd->freeNext);
    if (bd->freeNext == 0){
      // exhausted.
      _freeBuffDesc = nullptr;
    } else {
      _freeBuffDesc = _buffDesc + (_freeBuffDesc->freeNext - 1);
    }
    bd->freeNext = 0;
    
        index = bd->freeNext - 1;
        printf(">>>after index %d\r\n", index);
    return bd->buf_id;
    
}

void
BufferMgr::MarkBufferDirty(Buffer bufId) {

}
