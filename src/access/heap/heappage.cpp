#include "access/heap.hpp"
#include "storage/freespace.hpp"
#include "storage/bufmgr.hpp"
#include "access/rel.hpp"
#include "storage/page.hpp"

Buffer
Heap::_get_buffer_for_tuple(Relation rel, Size len) {
    Page page;
    Size pageFreeSpace;
    BlockNumber targetBlock;
    Buffer buffer = INVALID_BUFFER;

    // 获取 rel smgr里保存的target block
    targetBlock = rel->RelationGetTargetBlock();

    if (targetBlock == INVALID_BLOCK) {
        targetBlock = GetPageWithFreeSpace(rel, len);
    }

    while (targetBlock != INVALID_BLOCK) {
        buffer = ReadBuffer(rel, targetBlock);

        // 检查 buffer的空间是否足够
        page = BufferGetPage(buffer);
        pageFreeSpace = PageGetFreeSpace(page);
        if (len < pageFreeSpace) {
            rel->RelationSetTargetBlock(targetBlock);
            return buffer;
        }

        // 空间不足，查询fsm获取新的block
        targetBlock = RecordAndGetPageWithFreeSpace(rel, targetBlock, pageFreeSpace, len);
    }

    // 没有找到page，需要extend 空间
    buffer = ReadBuffer(rel, P_NEW);
    page = BufferGetPage(buffer);
    PageInit(page, BLKSZ, 0);

    rel->RelationSetTargetBlock(BufferGetBlockNumber(buffer));

    return buffer;
}

/*
insert the heap tuple into relation
*/
void
Heap::_relation_put_heap_tuple(Relation rel, Buffer buf, HeapTuple htup) {
    OffsetNumber offset;
    Page page = BufferGetPage(buf);

    if (PageIsNew(page)) {
        PageInit(page, BLKSZ, 0);
    }

    offset = PageAddItem(page, (htup->t_data), htup->t_len, InvalidOffsetNumber);

    htup->t_data->t_ctid.ip_blkno = GetBufferDesc(buf)->tag.blockNum;
    htup->t_data->t_ctid.ip_offset = offset;

    // 更新 ctid 相关数据
    ItemId itemId = PageGetItemId(page, offset);
    HeapTupleHeader item = (HeapTupleHeader)PageGetItem(page, itemId);
    item->t_ctid = htup->t_data->t_ctid;
}