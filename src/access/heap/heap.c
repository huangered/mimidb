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

    buffer = GetBufferForTuple(rel, htup->t_len);

    RelationPutHeapTuple(rel, buffer, htup);
    
    // todo
    //slot->tts_tid = ;
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
        if (tup->t_data->t_heap.t_xmax == 0) { // for now , only get latest one.
            tup->t_data->t_heap.t_xmax = cur_tran;
            // add new deleted record?!
            return true;
        }
        else {
            blkNum = tup->t_data->t_ctid.blocknum;
            offset = tup->t_data->t_ctid.offset;
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

    for (;;) {
        if (blkno > scan->num_blocks) {
            return false;
        }

        buf = ReadBuffer(scan->rel, MAIN_FORKNUMBER, blkno);

        Page page = BufferGetPage(buf);
        OffsetNumber max = PageGetMaxOffsetNumber(page);
        for (; offset <= max; offset++) {
            ItemId itemid = PageGetItemId(page, offset);
            Item item = PageGetItem(page, itemid);
            HeapTupleHeader tup = (HeapTupleHeader)item;

            char* data = (char*)tup + tup->t_hoff;
            int key = *((int*)data);
            int value = *(((int*)data) + 1 );

            if (key == scan->key) {
                scan->value = value;
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
        ItemId itemid = PageGetItemId(page, offset);
        Item item = PageGetItem(page, itemid);
        printf("itemid: %d %d", itemid->lp_len, itemid->lp_off);
        HeapTupleHeader tup = (HeapTupleHeader)item;
        int* ptr = (char*)tup + tup->t_hoff;
        int key = *ptr;
        int value = *(ptr + 1);
        printf("key %d, value %d", key, value);
    }
}