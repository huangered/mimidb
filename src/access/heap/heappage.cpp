#include "access/heap.hpp"
#include "storage/freespace.hpp"
#include "storage/bufmgr.hpp"

Buffer GetBufferForTuple(Relation rel, Size len) {
    BlockNumber blkno;
    Buffer buf;

    blkno = GetPageWithFreeSpace(rel, len);

    if (blkno != INVALID_BLOCK) {
        buf = ReadBuffer(rel, MAIN_FORKNUM, blkno);
        Page page = BufferGetPage(buf);

        if (PageIsNew(page)) {
            PageInit(page, BLKSZ, 0);
        }

        Size avail = PageGetFreeSpace(page) - len;
        BlockNumber blkno = GetBufferDesc(buf)->tag.blockNum;
        RecordPageWithFreeSpace(rel, blkno, avail);
        return buf;
    }

    return INVALID_BUFFER;
}

/*
insert the heap tuple into relation
*/
void RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup) {
    OffsetNumber offset;
    Page page = BufferGetPage(buf);

    if (PageIsNew(page)) {
        PageInit(page, BLKSZ, 0);
    }

    offset = PageAddItem(page, (htup->t_data), htup->t_len, InvalidOffsetNumber);

    htup->t_data->t_ctid.blocknum = GetBufferDesc(buf)->tag.blockNum;
    htup->t_data->t_ctid.offset = offset;
}