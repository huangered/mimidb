#include "access/heap.h"
#include "storage/page.h"
#include "storage/bufmgr.h"

typedef struct HeapTupleData {
    int xmin;
    int xmax;
    int ctid;
    int tag;
    int key;
    int value;
} HeapTupleData;

typedef HeapTupleData* HeapTuple;

#define HOT_UPDATED 0
#define HOT_REMOVED 1
#define HOT_NORMAL 2

#define HighKeyHot(hot) (( hot->ctid & 0xff00 ) >> 8 )
#define LowKeyHot(hot)  ( hot->ctid & 0x00ff )

void heapbuildempty(Relation rel) {
    // create relation file;
}

bool heapinsert(Relation rel, int key, int value) {

    return false;
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