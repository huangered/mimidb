#include "access/heap.h"
#include "storage/page.h"
#include "storage/bufmgr.h"

#define HOT_UPDATED 0
#define HOT_REMOVED 1
#define HOT_NORMAL 2

#define HighKeyHot(hot) (( hot->ctid & 0xff00 ) >> 8 )
#define LowKeyHot(hot)  ( hot->ctid & 0x00ff )

void heapbuildempty(Relation rel) {
    // create relation file;
}

bool heapinsert(Relation rel, int key, int value) {
    HeapTuple htup = _heap_buildtuple(key, value);
    Buffer buffer;

    buffer = GetBufferForTuple(rel, htup->len);

    RelationPutHeapTuple(rel, buffer, htup);
    
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
bool heapgettuple(Relation rel, int key, int* value) {
    BlockNum blkNum = 0;
    int offset = 0;
    Buffer buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkNum);

    Page page = BufferGetPage(buf);

    PageHeader pHeader = (PageHeader)page;
    for(;;) {
        ItemId itemId = PageGetItemId(page, offset);
        Item item = PageGetItem(page, itemId);

        HeapTuple tup = (HeapTuple)item;
        if (tup->xmax == 0) { // for now , only get latest one.
            *value = tup->value;
            return true;
        }
        else {
            blkNum = (tup->ctid & 0xff00) >> 8;
            offset = (tup->ctid & 0x00ffff);
        }
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