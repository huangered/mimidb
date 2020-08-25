#include "access/heap.h"
#include "storage/page.h"
#include "storage/bufmgr.h"
#include "util/mctx.h"
#include "access/tbapi.h"

#define HOT_UPDATED 0
#define HOT_REMOVED 1
#define HOT_NORMAL 2

#define HighKeyHot(hot) (( hot->ctid & 0xff00 ) >> 8 )
#define LowKeyHot(hot)  ( hot->ctid & 0x00ff )

TableAmRoute* table_route() {
    TableAmRoute* route = palloc(sizeof(TableAmRoute));
    route->buildempty = heapbuildempty;
    route->tuple_insert = heapinsert;
    route->gettuple = heapgettuple;
    route->tuple_remove = heapremove;
    return route;
}

void heapbuildempty(Relation rel) {
    // create relation file;
}

bool heapinsert(Relation rel, TupleSlotDesc* slot) {
    HeapTuple htup = _heap_buildtuple(rel, slot);
    Buffer buffer;

    buffer = GetBufferForTuple(rel, htup->len);

    RelationPutHeapTuple(rel, buffer, htup);
    
    slot->tts_tid = htup->ctid;
    return true;
}
bool heapremove(Relation rel, int key) {

    BlockNum blkNum = 0;
    int offset = 0;
    int cur_tran = 0xffff;
    Buffer buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkNum);

    Page page = BufferGetPage(buf);

    PageHeader pHeader = (PageHeader)page;
    for (;;) {
        ItemId itemId = PageGetItemId(page, offset);
        Item item = PageGetItem(page, itemId);

        HeapTuple tup = (HeapTuple)item;
        if (tup->xmax == 0) { // for now , only get latest one.
            tup->xmax = cur_tran;
            // add new deleted record?!
            return true;
        }
        else {
            blkNum = HighKeyHot(tup);
            offset = LowKeyHot(tup);
        }
    }

    return false;
}
bool heapgettuple(HeapScanDesc scan) {

    BlockNum blkno;
    OffsetNumber offset;
    Page page;
    Buffer buf;

    if (!scan->inited) {
        BlockNum start = 1;
        blkno = start;
        offset = FirstOffsetNumber;
        scan->inited = true;
    }
    else {
        blkno = scan->cblock;
        offset = OffsetNumberNext(scan->offset);
    }

    if (blkno > scan->num_blocks) {
        return false;
    }

    for (;;) {
        buf = ReadBuffer(scan->rel, MAIN_FORKNUMBER, blkno);

        Page page = BufferGetPage(buf);
        OffsetNumber max = PageGetMaxOffsetNumber(page);
        for (; offset <= max; offset++) {
            Item item = PageGetItem(page, PageGetItemId(page, offset));
            HeapTuple tup = (HeapTuple)item;
            if (tup->key == scan->key) {
                scan->value = tup->value;
                scan->cblock = blkno;
                scan->offset = offset;
                return true;
            }
        }
        // current page is exhausted.
        // goto next page
        blkno = blkno + 1;
        offset = FirstOffsetNumber;
    }
    return false;
}

// for debug
void print_heap(Relation rel) {
    BlockNum blkno = rel->root_blkno;
    Buffer buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
    Page page = BufferGetPage(buf);
    OffsetNumber max = PageGetMaxOffsetNumber(page);
    for (OffsetNumber offset = 1; offset <= max; offset++) {
        Item item = PageGetItem(page, PageGetItemId(page, offset));
        HeapTuple tup = (HeapTuple)item;
        printf("blkno: %d, offset: %d, key: %d, value: %d\r\n", HighKeyHot(tup), LowKeyHot(tup), tup->key, tup->value);
    }
}