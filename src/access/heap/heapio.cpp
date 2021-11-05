#include "access/heap.hpp"
#include "access/heapio.hpp"
#include "storage/freespace.hpp"
#include "storage/bufmgr.hpp"
#include "access/rel.hpp"
#include "storage/page.hpp"

void
RelationPutHeapTuple(Relation rel, Buffer buffer, HeapTuple htup) {
    OffsetNumber offset;
    Page page = BufferGetPage(buffer);

    if (PageIsNew(page)) {
        PageInit(page, BLKSZ, 0);
    }

    offset = PageAddItem(page, (htup->t_data), htup->t_len, InvalidOffsetNumber, true);

    htup->t_data->t_ctid.ip_blkno = BufferGetBlockNumber(buffer);
    htup->t_data->t_ctid.ip_offset = offset;

    // 更新 ctid 相关数据
    ItemId itemId        = PageGetItemId(page, offset);
    HeapTupleHeader item = (HeapTupleHeader)PageGetItem(page, itemId);
    item->t_ctid         = htup->t_data->t_ctid;
}

Buffer
RelationGetBufferForTuple(Relation rel, Size len) {
    Page page;
    Size pageFreeSpace;
    BlockNumber targetBlock;
    Buffer buffer = INVALID_BUFFER;

    // 获取 rel smgr里保存的target block
    targetBlock = RelationGetTargetBlock(rel);

    if (targetBlock == INVALID_BLOCK) {
        targetBlock = GetPageWithFreeSpace(rel, len);
    }

    while (targetBlock != INVALID_BLOCK) {
        buffer = ReadBuffer(rel, targetBlock);

        // 检查 buffer的空间是否足够
        page          = BufferGetPage(buffer);
        pageFreeSpace = PageGetFreeSpace(page);
        if (len <= pageFreeSpace) {
            RelationSetTargetBlock(rel, targetBlock);
            return buffer;
        }

        // 空间不足，查询fsm获取新的block
        targetBlock = RecordAndGetPageWithFreeSpace(rel, targetBlock, pageFreeSpace, len);
    }

    // 没有找到page，需要extend 空间
    buffer = ReadBuffer(rel, P_NEW);
    page   = BufferGetPage(buffer);
    PageInit(page, BLKSZ, 0);

    RelationSetTargetBlock(rel, BufferGetBlockNumber(buffer));

    return buffer;
}
