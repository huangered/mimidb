#include "access/rel.hpp"
#include "storage/buf_internal.hpp"
#include "storage/smgr.hpp"
#include "storage/bufmgr.hpp"

static HashMap<BufferTag, Buffer> _hashMap;

static void _Cleanup();
static Buffer _ReadBufferCommon(Relation rel, ForkNumber forkNumber, BlockNumber blkno);
static BufferDesc* _BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno, bool* found);
static void FlushBuffer(BufferDesc* buf);

BlockNumber
BufferGetBlockNumber(Buffer buffer) {
  BufferDesc* desc = GetBufferDescriptor(buffer - 1);
  return desc->tag.blockNum;
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
        GetBufferDescriptor(buf_id)->refcnt += 1;
        return GetBufferDescriptor(buf_id);
    }
    // if find, return
    // create new one and find a valid buffdesc or find a victim;
    buf_id = FindFreeBuffer();
    assert(buf_id <= NBuffers);
    assert(buf_id != INVALID_BUFFER);
    BufferDesc* desc = GetBufferDescriptor(buf_id);
    assert(desc);
    desc->refcnt += 1;
    desc->tag = tag;
    // insert into hash
    _hashMap.Put(tag, buf_id);
    return GetBufferDescriptor(buf_id);
}

void
ReleaseBuffer(Buffer buffer) {
    BufferDesc* bd = GetBufferDescriptor(buffer - 1);
    bd->refcnt -= 1;
}

void
FlushOneBuffer(Buffer buffer) {
    BufferDesc* buffDesc = GetBufferDescriptor(buffer - 1);
    FlushBuffer(buffDesc);
}

void
FlushBuffer(BufferDesc* buffDesc) {
    SMgrRelation reln = smgr->Open(buffDesc->tag.rnode);
    Page buf          = BufferGetPage(buffDesc->buf_id);
    smgr->Write(reln, buffDesc->tag.forkNum, buffDesc->tag.blockNum, buf);
}

void
MarkBufferDirty(Buffer buf) {
    BufferDesc* bd = GetBufferDescriptor(buf - 1);
    bd->dirty      = true;
    // flush to disk force now.
    FlushBuffer(bd);
}

void
LockBuffer(Buffer buf, int mode) {
}

