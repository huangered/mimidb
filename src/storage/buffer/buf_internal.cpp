#include "access/rel.hpp"
#include "storage/buf_internal.hpp"
#include "storage/smgr.hpp"
#include "storage/bufmgr.hpp"

#define NBuffer 32

BufferMgr::BufferMgr() {
    size_t size = NBuffer * BLKSZ;
    _blocks     = (char*)std::malloc(size);
    assert(_blocks);
    memset(_blocks, 0, size);

    _buffDesc = new BufferDesc[NBuffer]{};

    for (int i{ 0 }; i < NBuffer; i++) {
        BufferDesc* desc = &_buffDesc[i];
        desc->buf_id     = i + 1;
        desc->freeNext   = i + 2;
    }

    _buffDesc[NBuffer - 1].freeNext = INVALID_BUFFER;
    _freeBuffDesc                   = _buffDesc;
    // index = 0;
}

BufferMgr::~BufferMgr() {
    std::free(_blocks);
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
    desc      = _BufferAlloc(rel, forkNumber, blkno, &found);
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
    } else {
        smgr->Read(rel->rd_smgr, forkNumber, blkno, page);
    }
    return desc->buf_id;
}

BufferDesc*
BufferMgr::_BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno, bool* found) {
    Buffer buf_id = INVALID_BUFFER;
    BufferTag tag{ rel->rd_node, forkNumber, blkno };

    // use buftag to find
    *found = _hashMap.Get(tag, &buf_id);

    if (buf_id > INVALID_BUFFER) {
        // add ref count;
        GetBufferDesc(buf_id)->refcnt += 1;
        return GetBufferDesc(buf_id);
    }
    // if find, return
    // create new one and find a valid buffdesc or find a victim;
    buf_id = _FindFreeBuffer();
    assert(buf_id <= NBuffer);
    assert(buf_id != INVALID_BUFFER);
    BufferDesc* desc = GetBufferDesc(buf_id);
    assert(desc);
    desc->refcnt += 1;
    desc->tag = tag;
    // insert into hash
    _hashMap.Put(tag, buf_id);
    return GetBufferDesc(buf_id);
}

void
BufferMgr::ReleaseBuffer(Buffer buffer) {
    BufferDesc* bd = GetBufferDesc(buffer);
    bd->refcnt -= 1;
}

void
BufferMgr::FlushBuffer(BufferDesc* buffDesc) {
    SMgrRelation reln = smgr->Open(buffDesc->tag.rnode);
    char* buf         = GetPage(buffDesc->buf_id);
    smgr->Write(reln, buffDesc->tag.forkNum, buffDesc->tag.blockNum, buf);
}

Page
BufferMgr::GetPage(Buffer bufId) {
    int index1 = (bufId - 1) * BLKSZ;
    char* page = _blocks + index1;
    return page;
}

BufferDesc*
BufferMgr::GetBufferDesc(Buffer bufId) {
    BufferDesc* bd = &_buffDesc[bufId - 1];
    return bd;
}

void
BufferMgr::MarkBufferDirty(Buffer bufId) {
    BufferDesc* bd = &_buffDesc[bufId - 1];
    bd->dirty      = true;
    // flush to disk force now.
    FlushBuffer(bd);
}

Buffer
BufferMgr::_FindFreeBuffer() {
    // loop to find a valid buffer desc
    _Cleanup();
    BufferDesc* bd = _freeBuffDesc;

    if (bd->freeNext == INVALID_BUFFER) {
        // exhausted.
        _freeBuffDesc = nullptr;
    } else {
        _freeBuffDesc = _buffDesc + (_freeBuffDesc->freeNext - 1);
    }
    bd->freeNext = 0;
    return bd->buf_id;
}

void
BufferMgr::_Cleanup() {
    if (_freeBuffDesc == nullptr) {
        for (int i{}; i < NBuffer; i++) {
            BufferDesc* desc = &_buffDesc[i];
            if (desc->refcnt == 0) {
                if (desc->dirty) {
                    FlushBuffer(desc);
                }
                _hashMap.Remove(desc->tag);
                if (_freeBuffDesc != nullptr) {
                    desc->freeNext = _freeBuffDesc->buf_id;
                } else {
                    desc->freeNext = INVALID_BUFFER;
                }
                _freeBuffDesc = desc;
            }
        }
    }
}

void
BufferMgr::Debug(void) {
    for (int i{ 0 }; i < NBuffer; i++) {
        BufferDesc* desc = &_buffDesc[i];
        printf("buf id %d , refcnt %d , dirty %d\r\n", desc->buf_id, desc->refcnt, desc->dirty);
    }
}
