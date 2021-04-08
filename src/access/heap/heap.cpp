#include "access/heap.hpp"
#include "storage/page.hpp"
#include "storage/bufmgr.hpp"
#include "access/relcache.hpp"
#include "access/rel.hpp"

#define HOT_UPDATED     0
#define HOT_REMOVED     1
#define HOT_NORMAL      2

static Heap heap{};

Heap* HeapRoute() {
    return &heap;
}

//临时方法，会移到事务管理器中
static int GetCurrentTransactionId(void) {
    static int i = 0;
    return i++;
}

// 打开relation
Relation
Heap::Open(Oid relaitonId) {
    // 从relation cache加载
    Relation rel = relcache->RelationIdGetRelation(relaitonId);
    if (rel->rd_rel->relkind != RELKIND_RELATION) {
        printf("rel %s is not a relation", rel->rd_rel->relname);
    }

    return rel;
}

// 关闭relation
void
Heap::Close(Relation rel) {
    // 从relation cache释放
    relcache->RelationClose(rel);
}

bool
Heap::Remove(Relation rel, int key) {

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

void
Heap::_heapGetTuple(HeapScanDesc scan) {

    BlockNumber blkno;
    OffsetNumber offset;
    Page page;
    Buffer buf;

    if (!scan->rs_inited) {
        BlockNumber start = 0;
        blkno = start;
        offset = FirstOffsetNumber;
        scan->rs_inited = true;
    }
    else {
        blkno = scan->rs_curblock;
        offset = OffsetNumberNext(scan->rs_curtuple.t_data->t_ctid.offset);
    }

    for (;;) {
        if (blkno > scan->rs_numblocks) {
            return;
        }

        buf = ReadBuffer(scan->rs_rd, blkno);

        Page page = BufferGetPage(buf);
        OffsetNumber max = PageGetMaxOffsetNumber(page);
        for (; offset <= max; offset++) {
            ItemId itemid = PageGetItemId(page, offset);
            Item item = PageGetItem(page, itemid);
            HeapTupleHeader tup = (HeapTupleHeader)item;
            // todo test scan key;
           /* char* data = (char*)tup + HEAP_TUPLE_HEADER_SIZE;
            int key = *((int*)data);
            int value = *(((int*)data) + 1 );

            if (key == scan->rs_key) {
                scan->value = value;
                scan->cblock = blkno;
                scan->offset = offset;
                return true;
            }*/
        }
        // current page is exhausted.
        // goto next page
        blkno = blkno + 1;
        offset = FirstOffsetNumber;
    }
}

HeapScanDesc
Heap::BeginScan(Relation rel, int nkeys, ScanKey key) {
    HeapScanDesc scan;

    // increase relation ref count
    scan = new HeapScanDescData{};
    scan->rs_rd = rel;
    scan->rs_nkeys = nkeys;
    scan->rs_key = new ScanKeyData[nkeys];
    memcpy(scan->rs_key, key, nkeys * sizeof(ScanKeyData));

    RelationOpenSmgr(rel);
    scan->rs_nblocks = smgr->Nblocks(rel->rd_smgr, MAIN_FORKNUM);
    scan->rs_startblock = 0;
    scan->rs_numblocks = scan->rs_nblocks;

    return scan;
}

HeapTuple
Heap::GetNext(HeapScanDesc scan) {
    _heapGetTuple(scan);
    return &scan->rs_curtuple;
}

bool
Heap::EndScan(HeapScanDesc scan) {
    // 释放 scan 当前buf
    bmgr->ReleaseBuffer(scan->rs_curbuf);
    // descease the relation ref count

    if (scan->rs_key) {
        delete scan->rs_key;
    }

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
    int xid = GetCurrentTransactionId();
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
    // 设置 （xmin， xmax）
    tup->t_data->t_heap.t_xmin = xmin;
    tup->t_data->t_heap.t_xmax = 0;
    return tup;
}
