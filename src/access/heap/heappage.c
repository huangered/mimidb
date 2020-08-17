#include "access/heap.h"
#include "storage/freespace.h"
#include "storage/bufmgr.h"

Buffer GetBufferForTuple(Relation rel, Size len) {
    BlockNum blkno;
    Buffer buf;

    blkno = GetPageWithFreeSpace(rel, len);

    if (blkno != INVALID_BLOCK) {
        buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
        return buf;
    }

    return -1;
}

void RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup) {
    Page page = BufferGetPage(buf);

    if (PageIsNew(page)) {
        PageInit(page, BLKSZ, 0);
    }

    OffsetNumber max = PageGetMaxOffsetNumber(page);
    max = OffsetNumberNext(max);

    PageAddItem(page, htup, htup->len, max);

    Size avail = PageGetFreeSpace(page);
    BlockNum blkno = GetBufferDesc(buf)->tag.blockNum;
    RecordPageWithFreeSpace(rel, blkno, avail);

}