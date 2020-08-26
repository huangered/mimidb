#include "access/heap.h"
#include "storage/freespace.h"
#include "storage/bufmgr.h"

Buffer GetBufferForTuple(Relation rel, Size len) {
    BlockNum blkno;
    Buffer buf;

    blkno = GetPageWithFreeSpace(rel, len);

    if (blkno != INVALID_BLOCK) {
        buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
        Page page = BufferGetPage(buf);
        Size avail = PageGetFreeSpace(page) - len;
        BlockNum blkno = GetBufferDesc(buf)->tag.blockNum;
        RecordPageWithFreeSpace(rel, blkno, avail);
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

    htup->t_data->t_ctid.blocknum = GetBufferDesc(buf)->tag.blockNum;
    htup->t_data->t_ctid.offset = max;

    PageAddItem(page, (htup->t_data), htup->t_len, max);
}