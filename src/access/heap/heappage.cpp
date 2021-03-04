#include "access/heap.hpp"
#include "storage/freespace.hpp"
#include "storage/bufmgr.hpp"

Buffer
HeapIndex::GetBufferForTuple(Relation rel, Size len) {
    BlockNumber blkno;
    Buffer buf;

    blkno = freespace::GetPageWithFreeSpace(rel, len);

    if (blkno != INVALID_BLOCK) {
        buf = _bufMgr->ReadBuffer(rel, MAIN_FORKNUM, blkno);
        Page page = _bufMgr->GetPage(buf);

        if (PageIsNew(page)) {
            PageInit(page, BLKSZ, 0);
        }

        Size avail = PageGetFreeSpace(page) - len;
        BlockNumber blkno = _bufMgr->GetBufferDesc(buf)->tag.blockNum;
        freespace::RecordPageWithFreeSpace(rel, blkno, avail);
        return buf;
    }

    return INVALID_BUFFER;
}

/*
insert the heap tuple into relation
*/
void
HeapIndex::RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup) {
    OffsetNumber offset;
    Page page = _bufMgr->GetPage(buf);

    if (PageIsNew(page)) {
        PageInit(page, BLKSZ, 0);
    }

    offset = PageAddItem(page, (htup->t_data), htup->t_len, InvalidOffsetNumber);

    htup->t_data->t_ctid.blocknum = _bufMgr->GetBufferDesc(buf)->tag.blockNum;
    htup->t_data->t_ctid.offset = offset;
}