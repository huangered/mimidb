#include "access/heap.hpp"
#include "storage/page.hpp"
#include "storage/bufmgr.hpp"
#include "access/relcache.hpp"

#define HOT_UPDATED     0
#define HOT_REMOVED     1
#define HOT_NORMAL      2

static Heap* heap = new Heap{};

Heap* route() {
    return heap;
}

// 打开relation
Relation
Heap::Open(Oid relaitonId) {
    return RelationIdGetRelation(relaitonId);
}

// 关闭relation
void
Heap::Close(Relation rel) {
    RelationClose(rel);
}

void Heap::heapbuildempty(Relation rel) {
    // create relation file;
}

bool Heap::heap_tuple_insert(Relation rel, TupleSlotDesc* slot) {

    HeapTuple htup = _heap_buildtuple(rel, slot);
    
    
    // todo
    //slot->tts_tid = ;
    return Insert(rel, htup);
}
bool Heap::Remove(Relation rel, int key) {

    BlockNumber blkNum = 0;
    int offset = 0;
    int cur_tran = 0xffff;
    Buffer buf = ReadBuffer(rel, blkNum);

    Page page = BufferGetPage(buf);

    PageHeader pHeader = (PageHeader)page;
    for (;;) {
        ItemId itemId = PageGetItemId(page, offset);
        Item item = PageGetItem(page, itemId);

        HeapTuple tup = (HeapTuple)item;
        if (tup->t_data->t_heap.t_xmax == 0) { // for now , only get latest one.
            tup->t_data->t_heap.t_xmax = cur_tran;
             //add new deleted record?!
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
Heap::heapgettuple(HeapScanDesc scan) {

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

        buf = ReadBuffer(scan->rs_base.rs_rel, blkno);

        Page page = BufferGetPage(buf);
        OffsetNumber max = PageGetMaxOffsetNumber(page);
        for (; offset <= max; offset++) {
            ItemId itemid = PageGetItemId(page, offset);
            Item item = PageGetItem(page, itemid);
            HeapTupleHeader tup = (HeapTupleHeader)item;

            char* data = (char*)tup + HEAP_TUPLE_HEADER_SIZE;
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
Heap::BeginScan(Relation rel, int nkeys, ScanKey key) {
    HeapScanDesc scan;

    // increase relation ref count
    scan = new HeapScanDescData{};
    scan->rs_base.rs_rel = rel;
    scan->rs_base.rs_nkeys = nkeys;
    scan->rs_base.rs_key = key;
    return scan;
}

HeapTuple
Heap::GetNext(HeapScanDesc scan) {
    return NULL;
}

bool
Heap::EndScan(HeapScanDesc scan) {
    // descease the relation ref count

    delete scan->rs_base.rs_key;

    delete scan;
    return true;
}

/*
1. run the heap page vacuu
2. update the fsm page
*/
void 
Heap::Vacuum(Relation rel) {

}

/*
for catalog operation
*/
void
Heap::simple_heap_insert(Relation rel, HeapTuple tup) {
    Insert(rel, tup);
}

//插入操作
bool
Heap::Insert(Relation rel, HeapTuple htup) {
    // get current transition id.
    int xid = 0;
    Buffer buffer;

    htup = _tuple_prepare_insert(rel, htup, xid);

    buffer = GetBufferForTuple(rel, htup->t_len);

    RelationPutHeapTuple(rel, buffer, htup);

    MarkBufferDirty(buffer);

    return true;
}

/*
给heaptup的事务id赋值
*/
HeapTuple
Heap::_tuple_prepare_insert(Relation rel, HeapTuple tup, int xmin) {
    tup->t_data->t_heap.t_xmin = xmin;
    tup->t_data->t_heap.t_xmax = 0;
    return tup;
}

HeapTuple
Heap::_heap_buildtuple(Relation rel, TupleSlotDesc* slot) {
    HeapTuple a;
    return a;
}
