#include "access/heap.h"
#include "storage/freespace.h"
#include "storage/bufmgr.h"

Buffer GetBufferForTuple(Relation rel, Size len) {
    BlockNum blkno;
    Buffer buf;

    blkno = GetPageWithFreeSpace(rel, len);

    if (blkno != INVALID_BLOCK) {
        RecordPageWithFreeSpace(rel, blkno, 0);
        buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
        return buf;
    }

    return -1;
}

void RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup) {
    OffsetNumber offset = 0;
    Page page = BufferGetPage(buf);
    PageAddItem(page, htup, htup->len, offset);
}
