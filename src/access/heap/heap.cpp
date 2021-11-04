#include "access/heap.hpp"
#include "storage/page.hpp"
#include "storage/bufmgr.hpp"
#include "access/relcache.hpp"
#include "access/rel.hpp"
#include "util/mctx.hpp"

#define HOT_UPDATED 0
#define HOT_REMOVED 1
#define HOT_NORMAL  2

static Heap heap{};

Heap*
HeapRoute() {
    return &heap;
}

//临时方法，会移到事务管理器中
static int
GetCurrentTransactionId(void) {
    static int i = 0;
    return i++;
}

static bool
TestKey(HeapTuple tuple, HeapScanDesc scan) {
    bool result1{ true };
    char* data = (char*)tuple->t_data + HEAP_TUPLE_HEADER_SIZE;

    for (int i{ 0 }; i < scan->rs_nkeys; i++) {
        int key   = *((int*)data);
        int value = *(((int*)data) + 1);

        ScanKey skey = scan->rs_key + i;
        Datum result = DirectFunctionCall2Coll(skey->sk_func.fn_method, key, skey->sk_data);
        if (result != 0) {
            result1 = false;
            break;
        }
    }
    return result1;
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

Heap::Heap() {
}

bool
Heap::Remove(Relation rel, int key) {

    BlockNumber blkNum = 0;
    int offset         = 0;
    int cur_tran       = 0xffff;
    Buffer buf         = ReadBuffer(rel, blkNum);

    Page page = BufferGetPage(buf);

    PageHeader pHeader = (PageHeader)page;
    for (;;) {
        ItemId itemId = PageGetItemId(page, offset);
        Item item     = PageGetItem(page, itemId);

        HeapTuple tup = (HeapTuple)item;
        if (tup->t_data->t_heap.t_xmax == 0) { // for now , only get latest one.
            tup->t_data->t_heap.t_xmax = cur_tran;
            // add new deleted record?!
            return true;
        } else {
            blkNum = tup->t_data->t_ctid.ip_blkno;
            offset = tup->t_data->t_ctid.ip_offset;
        }
    }

    return false;
}

/*
现在只支持前向搜索
*/
void
Heap::_heap_get_tuple(HeapScanDesc scan, ScanDirection direction) {
    HeapTuple tuple = &(scan->rs_curtuple);
    BlockNumber blkno;
    OffsetNumber offset;
    OffsetNumber max;
    Page page;
    Buffer buf;

    if (!scan->rs_inited) {
        BlockNumber start = 0;
        blkno             = start;
        offset            = FirstOffsetNumber;
        scan->rs_inited   = true;
        tuple->t_data     = nullptr;
    } else {
        blkno  = scan->rs_curblock;
        offset = OffsetNumberNext(scan->rs_curtuple.t_data->t_ctid.ip_offset);
    }

    buf  = ReadBuffer(scan->rs_rd, blkno);
    page = BufferGetPage(buf);
    max  = PageGetMaxOffsetNumber(page);

    for (;;) {
        if (blkno > scan->rs_numblocks) {
            break;
        }

        for (; offset <= max; offset++) {
            ItemId itemid = PageGetItemId(page, offset);
            tuple->t_data = (HeapTupleHeader)PageGetItem(page, itemid);
            ;
            tuple->t_len = itemid->lp_len;
            // todo test scan key;

            if (TestKey(tuple, scan)) {
                scan->rs_curblock               = blkno;
                tuple->t_data->t_ctid.ip_blkno  = blkno;
                tuple->t_data->t_ctid.ip_offset = offset;
                return;
            }
        }
        // current page is exhausted.
        // goto next page
        blkno  = blkno + 1;
        offset = FirstOffsetNumber;

        buf  = ReadBuffer(scan->rs_rd, blkno);
        page = BufferGetPage(buf);
        max  = PageGetMaxOffsetNumber(page);
    }

    // search all blocks, no one found.
    tuple->t_data     = nullptr;
    scan->rs_inited   = false;
    scan->rs_curbuf   = INVALID_BUFFER;
    scan->rs_curblock = INVALID_BLOCK;
}

HeapScanDesc
Heap::BeginScan(Relation rel, int nkeys, ScanKey key) {
    HeapScanDesc scan{};

    // increase relation ref count
    scan           = new HeapScanDescData{};
    scan->rs_rd    = rel;
    scan->rs_nkeys = nkeys;
    scan->rs_key   = new ScanKeyData[nkeys];
    memcpy(scan->rs_key, key, nkeys * sizeof(ScanKeyData));

    RelationOpenSmgr(rel);
    scan->rs_nblocks    = smgr->Nblocks(rel->rd_smgr, MAIN_FORKNUM);
    scan->rs_startblock = 0;
    scan->rs_numblocks  = scan->rs_nblocks;

    return scan;
}

HeapTuple
Heap::GetNext(HeapScanDesc scan, ScanDirection direction) {
    _heap_get_tuple(scan, direction);
    return &scan->rs_curtuple;
}

bool
Heap::EndScan(HeapScanDesc scan) {
    // 释放 scan 当前buf
    ReleaseBuffer(scan->rs_curbuf);
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

    buffer = _get_buffer_for_tuple(rel, htup->t_len);

    _relation_put_heap_tuple(rel, buffer, htup);

    MarkBufferDirty(buffer);
    FlushOneBuffer(buffer);
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

void
Heap::debug(Relation rel) {
    int j{ 0 };
    RelationOpenSmgr(rel);
    int nblocks = smgr->Nblocks(rel->rd_smgr, MAIN_FORKNUM);
    for (int i{}; i < nblocks; i++) {
        Buffer buf       = ReadBuffer(rel, i);
        Page page        = BufferGetPage(buf);
        OffsetNumber max = PageGetMaxOffsetNumber(page);

        for (OffsetNumber offset{ 1 }; offset <= max; offset++) {
            ItemId itemid       = PageGetItemId(page, offset);
            Item item           = PageGetItem(page, itemid);
            HeapTupleHeader tup = (HeapTupleHeader)item;
            // todo test scan key;
            char* data = (char*)tup + HEAP_TUPLE_HEADER_SIZE;
            int* a     = (int*)data;
            printf(">>> debug min,max: (%d , %d) bo, (%d, %d) value: (%d , %d)\r\n", tup->t_heap.t_xmin,
                   tup->t_heap.t_xmax, tup->t_ctid.ip_blkno, tup->t_ctid.ip_offset, *a, *(a + 1));
            j++;
        }
        printf(">>>\r\n");
        ReleaseBuffer(buf);
    }
    printf("total %d\r\n", j);
}

/* public api */
Relation
relation_open(Oid relationId) {
    // 从relation cache加载
    Relation r;
    r = relcache->RelationIdGetRelation(relationId);
    if (r->rd_rel->relkind != RELKIND_RELATION) {
        printf("rel %s is not a relation", r->rd_rel->relname);
    }

    return r;
}

void
relation_close(Relation relation) {
    relcache->RelationClose(relation);
}

Relation
heap_open(Oid relationId) {
    Relation r;
    r = relation_open(relationId);

    return r;
}

void
heap_close(Relation relation) {
    relation_close(relation);
}

HeapScanDesc
heap_beginscan(Relation rel, int nkeys, ScanKey key) {
    HeapScanDesc scan;

    // increment relation ref count

    // alloc scan desc

    scan = (HeapScanDesc)palloc(sizeof(HeapScanDescData));
    return NULL;
}

void
heap_endscan(HeapScanDesc scan) {
}

HeapTuple
heap_getnext(HeapScanDesc scan, ScanDirection direction) {
    return NULL;
}

Oid
heap_insert(Relation relation, HeapTuple tup) {
    return 0;
}
void
heap_delete(Relation relation, ItemPointer tid) {
}

/*
 * force sync relation to disk
 */
void
heap_sync(Relation relation) {
}
