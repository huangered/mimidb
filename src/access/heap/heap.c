#include "access/heap.h"
#include "storage/page.h"
#include "storage/bufmgr.h"
#include "util/mctx.h"
#include "access/tbapi.h"

#define HOT_UPDATED     0
#define HOT_REMOVED     1
#define HOT_NORMAL      2

static bool heap_insert(Relation rel, HeapTuple tup);


static const TableAmRoute route = {
    .buildempty = heapbuildempty,
    .tuple_insert = heap_tuple_insert,
    .gettuple = heapgettuple,
    .tuple_remove = heapremove,
    .beginscan = heapbeginscan,
    .endscan = heapendscan,
    .getnext = heapgetnext,
    .vacuum = heap_vacuum
};

TableAmRoute* table_route() {
    return &route;
}

void heapbuildempty(Relation rel) {
    // create relation file;
}

bool heap_tuple_insert(Relation rel, TupleSlotDesc* slot) {
    HeapTuple htup = _heap_buildtuple(rel, slot);
    
    
    // todo
    //slot->tts_tid = ;
    return heap_insert(rel, htup);
}
bool heapremove(Relation rel, int key) {

    BlockNumber blkNum = 0;
    int offset = 0;
    int cur_tran = 0xffff;
    Buffer buf = ReadBuffer(rel, MAIN_FORKNUM, blkNum);

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

    BlockNumber blkno;
    OffsetNumber offset;
    Page page;
    Buffer buf;

    if (!scan->inited) {
        BlockNumber start = 0;
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

        buf = ReadBuffer(scan->rel, MAIN_FORKNUM, blkno);

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

bool heapbeginscan(HeapScanDesc scan) {
    return false;
}
HeapTuple heapgetnext(HeapScanDesc scan) {
    return NULL;
}
bool heapendscan(HeapScanDesc scan) {
    // do nothing now.
    return true;
}

/*
1. run the heap page vacuu
2. update the fsm page
*/
void 
heap_vacuum(Relation rel) {

}

/*
for catalog operation
*/
void
simple_heap_insert(Relation rel, HeapTuple tup) {
    heap_insert(rel, tup);
}

// ========= private 

bool heap_insert(Relation rel, HeapTuple htup) {
    Buffer buffer;

    buffer = GetBufferForTuple(rel, htup->t_len);

    RelationPutHeapTuple(rel, buffer, htup);

    return true;
}

// for debug
void print_heap(Relation rel) {
    BlockNumber blkno = rel->root_blkno;
    TupleDesc tupdesc = rel->tupleDesc;
    Buffer buf = ReadBuffer(rel, MAIN_FORKNUM, blkno);
    Page page = BufferGetPage(buf);
    OffsetNumber max = PageGetMaxOffsetNumber(page);
    for (OffsetNumber offset = 1; offset <= max; offset++) {
        ItemId itemid = PageGetItemId(page, offset);
        Item item = PageGetItem(page, itemid);
        printf("\r\nitemid: %d %d\r\n", itemid->lp_len, itemid->lp_off);
        HeapTupleHeader tup = (HeapTupleHeader)item;

        int offset = 0;
        for (int i = 0; i < tupdesc->natts; i++) {
            FormData_mimi_attribute attr = tupdesc->attr[i];

            int* ptr = ((char*)tup + tup->t_hoff + offset);
            printf("value: %d", *ptr);
            offset += attr.attlen;
        }
    }
}