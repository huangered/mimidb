#include "access/heap.h"
#include "access/heapio.h"
#include "storage/page.h"
#include "storage/bufmgr.h"
#include "access/relcache.h"
#include "access/rel.h"

#define HOT_UPDATED 0
#define HOT_REMOVED 1
#define HOT_NORMAL  2

static HeapTuple _tuple_prepare_insert(Relation rel, HeapTuple tup, int xmin);
static void initscan(HeapScanDesc scan, ScanKey key);
static void _heap_get_tuple(HeapScanDesc scan, enum ScanDirection direction);

/*
 * heap support method
 */
void
initscan(HeapScanDesc scan, ScanKey key) {
    scan->rs_nblocks    = RelationGetNumberOfBlocksInFork(scan->rs_rd, MAIN_FORKNUM);
    scan->rs_startblock = 0;
    scan->rs_numblocks  = scan->rs_nblocks;

    scan->rs_inited          = false;
    scan->rs_curtuple.t_data = NULL;
    scan->rs_curbuf          = INVALID_BUFFER;
    scan->rs_curblock        = INVALID_BLOCK;

    if (key != NULL)
        memcpy(scan->rs_key, key, scan->rs_nkeys * sizeof(struct ScanKeyData));
}

//临时方法，会移到事务管理器中
static int
GetCurrentTransactionId(void) {
    static int i = 0;
    return i++;
}

static bool
TestKey(HeapTuple tuple, HeapScanDesc scan) {
    bool result1 = true;
    char* data   = (char*)tuple->t_data + HEAP_TUPLE_HEADER_SIZE;

    for (int i = 0; i < scan->rs_nkeys; i++) {
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

/*
 * 现在只支持前向搜索
 */
void
_heap_get_tuple(HeapScanDesc scan, enum ScanDirection direction) {
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
        tuple->t_data     = NULL;
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
            tuple->t_len  = itemid->lp_len;
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
    tuple->t_data     = NULL;
    scan->rs_inited   = false;
    scan->rs_curbuf   = INVALID_BUFFER;
    scan->rs_curblock = INVALID_BLOCK;
}

/*
给heaptup的事务id赋值
*/
HeapTuple
_tuple_prepare_insert(Relation rel, HeapTuple tup, int xmin) {
    // 设置 （xmin， xmax）
    tup->t_data->t_heap.t_xmin = xmin;
    tup->t_data->t_heap.t_xmax = 0;
    return tup;
}

/* public api */
Relation
relation_open(Oid relationId) {
    // 从relation cache加载
    Relation r;
    // todo: r = relcache->RelationIdGetRelation(relationId);
    if (r->rd_rel->relkind != RELKIND_RELATION) {
        printf("rel %s is not a relation", r->rd_rel->relname);
    }

    return r;
}

void
relation_close(Relation relation) {
    // todo: relcache->RelationClose(relation);
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
    scan = (HeapScanDesc)palloc(sizeof(struct HeapScanDescData));

    scan->rs_rd    = rel;
    scan->rs_nkeys = nkeys;

    // init scankey
    if (nkeys > 0) {
        scan->rs_key = (ScanKey)palloc(sizeof(struct ScanKeyData) * nkeys);
    } else {
        scan->rs_key = NULL;
    }

    initscan(scan, key);

    return scan;
}

void
heap_endscan(HeapScanDesc scan) {

    // 释放 scan 当前buf
    if (BufferIsValid(scan->rs_curbuf))
        ReleaseBuffer(scan->rs_curbuf);

    // descease the relation ref count

    if (scan->rs_key) {
        pfree(scan->rs_key);
    }

    pfree(scan);
}

HeapTuple
heap_getnext(HeapScanDesc scan, enum ScanDirection direction) {
    _heap_get_tuple(scan, direction);
    return &scan->rs_curtuple;
}

Oid
heap_insert(Relation relation, HeapTuple htup) {
    // get current transition id.
    int xid = GetCurrentTransactionId();
    Buffer buffer;

    htup = _tuple_prepare_insert(relation, htup, xid);

    buffer = RelationGetBufferForTuple(relation, htup->t_len);

    RelationPutHeapTuple(relation, buffer, htup);

    MarkBufferDirty(buffer);
    FlushOneBuffer(buffer);
    return 1;
}
void
heap_delete(Relation relation, ItemPointer tid) {
    BlockNumber blkNum = 0;
    int offset         = 0;
    int cur_tran       = 0xffff;
    Buffer buf         = ReadBuffer(relation, blkNum);

    Page page = BufferGetPage(buf);

    PageHeader pHeader = (PageHeader)page;
    for (;;) {
        ItemId itemId = PageGetItemId(page, offset);
        Item item     = PageGetItem(page, itemId);

        HeapTuple tup = (HeapTuple)item;
        if (tup->t_data->t_heap.t_xmax == 0) { // for now , only get latest one.
            tup->t_data->t_heap.t_xmax = cur_tran;
            // add new deleted record?!
        } else {
            blkNum = tup->t_data->t_ctid.ip_blkno;
            offset = tup->t_data->t_ctid.ip_offset;
        }
    }
}

/*
 * force sync relation to disk
 */
void
heap_sync(Relation relation) {
}

void
simple_heap_insert(Relation relation, HeapTuple tup) {
    heap_insert(relation, tup);
}
