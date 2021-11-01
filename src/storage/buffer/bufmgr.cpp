#include "access/rel.hpp"
#include "storage/buf_internal.hpp"
#include "storage/smgr.hpp"
#include "storage/bufmgr.hpp"

#define NBuffer 32

char* BufferBlocks;
static BufferDesc* _buffDesc;
static BufferDesc* _freeBuffDesc;
static HashMap<BufferTag, Buffer> _hashMap;

static void _Cleanup();
static Buffer _ReadBufferCommon(Relation rel, ForkNumber forkNumber, BlockNumber blkno);
static BufferDesc* _BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno, bool* found);
static Buffer _FindFreeBuffer();
static void FlushBuffer(BufferDesc* buf);

void
BufferInit() {
    size_t size  = NBuffer * BLKSZ;
    BufferBlocks = (char*)std::malloc(size);

    memset(BufferBlocks, 0, size);

    _buffDesc = new BufferDesc[NBuffer]{};

    for (int i{ 0 }; i < NBuffer; i++) {
        BufferDesc* desc = &_buffDesc[i];
        desc->buf_id     = i + 1;
        desc->freeNext   = i + 2;
    }

    _buffDesc[NBuffer - 1].freeNext = INVALID_BUFFER;
    _freeBuffDesc                   = _buffDesc;
}

BlockNumber
BufferGetBlockNumber(Buffer buffer) {
    return 0;
}

Buffer
ReadBuffer(Relation rel, BlockNumber blkno) {
    return ReadBufferExtend(rel, MAIN_FORKNUM, blkno);
}

Buffer
ReadBufferExtend(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
    RelationOpenSmgr(rel);

    return _ReadBufferCommon(rel, forkNumber, blkno);
}

/*
 */
Buffer
_ReadBufferCommon(Relation rel, ForkNumber forkNumber, BlockNumber blkno) {
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
    Page page = BufferGetPage(desc->buf_id);
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
_BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno, bool* found) {
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
ReleaseBuffer(Buffer buffer) {
    BufferDesc* bd = GetBufferDesc(buffer);
    bd->refcnt -= 1;
}

void
FlushOneBuffer(Buffer buffer) {
    BufferDesc* buffDesc = GetBufferDesc(buffer);
    FlushBuffer(buffDesc);
}

void
FlushBuffer(BufferDesc* buffDesc) {
    SMgrRelation reln = smgr->Open(buffDesc->tag.rnode);
    char* buf         = BufferGetPage(buffDesc->buf_id);
    smgr->Write(reln, buffDesc->tag.forkNum, buffDesc->tag.blockNum, buf);
}

Page
BufferGetPage(Buffer bufId) {
    int index1 = (bufId - 1) * BLKSZ;
    char* page = BufferBlocks + index1;
    return page;
}

BufferDesc*
GetBufferDesc(Buffer bufId) {
    BufferDesc* bd = &_buffDesc[bufId - 1];
    return bd;
}

void
MarkBufferDirty(Buffer bufId) {
    BufferDesc* bd = &_buffDesc[bufId - 1];
    bd->dirty      = true;
    // flush to disk force now.
    FlushBuffer(bd);
}

void
LockBuffer(Buffer buf, int mode) {
}

Buffer
_FindFreeBuffer() {
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
_Cleanup() {
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
Debug(void) {
    for (int i{ 0 }; i < NBuffer; i++) {
        BufferDesc* desc = &_buffDesc[i];
        printf("buf id %d , refcnt %d , dirty %d\r\n", desc->buf_id, desc->refcnt, desc->dirty);
    }
}
