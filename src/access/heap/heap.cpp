#include "access/heap.hpp"
#include "storage/page.hpp"
#include "storage/bufmgr.hpp"
#include "util/mctx.hpp"
#include "access/tbapi.hpp"

#define HOT_UPDATED     0
#define HOT_REMOVED     1
#define HOT_NORMAL      2


static TableAmRoute route = {
    /*.buildempty = heapbuildempty,
    .tuple_insert = heap_tuple_insert,
    .tuple_remove = heapremove,
    .gettuple = heapgettuple,
    .beginscan = heapbeginscan,
    .getnext = heapgetnext,
    .endscan = heapendscan,
    .vacuum = heap_vacuum*/
};

TableAmRoute* table_route() {
    return &route;
}

void HeapIndex::heapbuildempty(Relation rel) {
    // create relation file;
}

bool HeapIndex::heap_tuple_insert(Relation rel, TupleSlotDesc* slot) {

    HeapTuple htup = _heap_buildtuple(rel, slot);
    
    
    // todo
    //slot->tts_tid = ;
    return heap_insert(rel, htup);
}
bool HeapIndex::heapremove(Relation rel, int key) {

    BlockNumber blkNum = 0;
    int offset = 0;
    int cur_tran = 0xffff;
    Buffer buf = _bufMgr->ReadBuffer(rel, blkNum);

    Page page = _bufMgr->GetPage(buf);

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
bool
HeapIndex::heapgettuple(HeapScanDesc scan) {

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

        buf = _bufMgr->ReadBuffer(scan->rs_base.rs_rel, blkno);

        Page page = _bufMgr->GetPage(buf);
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

HeapScanDesc
HeapIndex::heapbeginscan(Relation rel, int nkeys, ScanKey key) {
    HeapScanDesc scan;

    // increase relation ref count
    scan = (HeapScanDesc)palloc(sizeof(HeapScanDescData));
    scan->rs_base.rs_rel = rel;
    scan->rs_base.rs_nkeys = nkeys;
    scan->rs_base.rs_key = key;
    return scan;
}

HeapTuple
HeapIndex::heapgetnext(HeapScanDesc scan) {
    return NULL;
}

bool
HeapIndex::heapendscan(HeapScanDesc scan) {
    // descease the relation ref count

    pfree(scan->rs_base.rs_key);

    pfree(scan);
    return true;
}

/*
1. run the heap page vacuu
2. update the fsm page
*/
void 
HeapIndex::heap_vacuum(Relation rel) {

}

/*
for catalog operation
*/
void
HeapIndex::simple_heap_insert(Relation rel, HeapTuple tup) {
    heap_insert(rel, tup);
}

// ========= private 

bool
HeapIndex::heap_insert(Relation rel, HeapTuple htup) {
    // get current transition id.
    int xid = 0;
    Buffer buffer;

    htup = heaptuple_prepare_insert(rel, htup, xid);

    buffer = GetBufferForTuple(rel, htup->t_len);

    RelationPutHeapTuple(rel, buffer, htup);

    return true;
}

/*
给heaptup的事务id赋值
*/
HeapTuple
HeapIndex::heaptuple_prepare_insert(Relation rel, HeapTuple tup, int xmin) {
    tup->t_data->t_heap.t_xmin = xmin;
    tup->t_data->t_heap.t_xmax = 0;
    return tup;
}

HeapTuple
HeapIndex::_heap_buildtuple(Relation rel, TupleSlotDesc* slot) {
    HeapTuple a;
    return a;
}


// for debug
void
HeapIndex::print_heap(Relation rel) {
    BlockNumber blkno = rel->root_blkno;
    TupleDesc tupdesc = rel->tupleDesc;
    Buffer buf = _bufMgr->ReadBuffer(rel, blkno);
    Page page = _bufMgr->GetPage(buf);
    OffsetNumber max = PageGetMaxOffsetNumber(page);
    for (OffsetNumber offset = 1; offset <= max; offset++) {
        ItemId itemid = PageGetItemId(page, offset);
        Item item = PageGetItem(page, itemid);
        printf("\r\nitemid: %d %d\r\n", itemid->lp_len, itemid->lp_off);
        HeapTupleHeader tup = (HeapTupleHeader)item;

        int offset1 = 0;
        for (int i = 0; i < tupdesc->natts; i++) {
            FormData_mimi_attribute attr = tupdesc->attr[i];

            int* ptr = (int*)((char*)tup + tup->t_hoff + offset);
            printf("value: %d", *ptr);
            offset += attr.att_len;
        }
    }
}