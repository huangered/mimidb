#include "access/rel.h"
#include "storage/buf_internal.h"
#include "storage/smgr.h"
#include "storage/bufmgr.h"

/* internal use */
#define BufHdrGetBlock(bufHdr) ((Block)(BufferBlocks + ((bufHdr)->buf_id) * BLKSZ))

static void _Cleanup();
static Buffer _ReadBufferCommon(Relation rel, ForkNumber forkNumber, BlockNumber blkno);
static struct BufferDesc* _BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno, bool* found);
static void FlushBuffer(struct BufferDesc* buf);

BlockNumber
BufferGetBlockNumber(Buffer buffer) {
   struct  BufferDesc* desc = GetBufferDescriptor(buffer - 1);
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
    Block bufBlock;
    struct BufferDesc* desc;
    bool found;
    bool isExtend;

    if (blkno == P_NEW) {
        isExtend = true;
    }

    if (isExtend) {
        // todo
        return 1;
        //blkno = smgr->Nblocks(rel->rd_smgr, forkNumber);
    }
    desc     = _BufferAlloc(rel, forkNumber, blkno, &found);
    bufBlock = BufHdrGetBlock(desc);
    if (found) {
        if (!isExtend) {
            return BufferDescriptorGetBuffer(desc);
        }
    }
    // load or save data
    if (isExtend) {
        memset(bufBlock, 0, BLKSZ);
        //todo:
        //smgr->Extend(rel->rd_smgr, forkNumber, blkno, (char*)bufBlock);
    } else {
        // todo
        //smgr->Read(rel->rd_smgr, forkNumber, blkno, (char*)bufBlock);
    }
    return BufferDescriptorGetBuffer(desc);
}

struct BufferDesc*
_BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno, bool* found) {
    Buffer buf_id = INVALID_BUFFER;
    BufferTag tag;
    //todo:
    //{ rel->rd_node, forkNumber, blkno };

    // use buftag to find
    //*found = _hashMap.Get(tag, &buf_id);

    if (*found) {
        // add ref count;
        GetBufferDescriptor(buf_id)->refcnt += 1;
        return GetBufferDescriptor(buf_id);
    }
    // if find, return
    // create new one and find a valid buffdesc or find a victim;
    struct BufferDesc* desc = FindFreeBuffer();

    assert(desc);
    desc->refcnt += 1;
    desc->tag = tag;
    // insert into hash
    //_hashMap.Put(tag, desc->buf_id);
    return desc;
}

void
ReleaseBuffer(Buffer buffer) {
    struct BufferDesc* bd = GetBufferDescriptor(buffer - 1);
    bd->refcnt -= 1;
}

void
FlushOneBuffer(Buffer buffer) {
    struct BufferDesc* buffDesc = GetBufferDescriptor(buffer - 1);
    FlushBuffer(buffDesc);
}

void
FlushBuffer(struct BufferDesc* buffDesc) {
//    SMgrRelation reln = smgr->Open(buffDesc->tag.rnode);
//    Page buf          = BufferGetPage(BufferDescriptorGetBuffer(buffDesc));
//    smgr->Write(reln, buffDesc->tag.forkNum, buffDesc->tag.blockNum, buf);
}

void
MarkBufferDirty(Buffer buf) {
    struct BufferDesc* bd = GetBufferDescriptor(buf - 1);
    bd->dirty      = true;
    // flush to disk force now.
    FlushBuffer(bd);
}

void
LockBuffer(Buffer buf, int mode) {
}

/*
 * RelationGetNumberOfBlocksInFork
 *		Determines the current number of pages in the specified relation fork.
 */
BlockNumber
RelationGetNumberOfBlocksInFork(Relation relation, ForkNumber forkNum) {
    /* Open it at the smgr level if not already done */
    RelationOpenSmgr(relation);

    //return smgr->Nblocks(relation->rd_smgr, forkNum);
    //todo: 
    return 1;
}
