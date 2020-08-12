#include "access/btree.h"
#include "access/rel.h"
#include "storage/page.h"
#include "util/mctx.h"

OffsetNumber _bt_binsrch(Relation rel, Page page, BTreeScan key) {
    int result;

    BTreeSpecial special = PageGetSpecial(page);
    int low = P_FIRSTDATAKEY(special);
    int high = PageGetMaxOffsetNumber(page);

    // for no data item
    if (high < low) {
        return low;
    }

    high++;

    int cmp = key->nextkey ? 0 : 1;
    while (low < high) {
        int mid = low + ((high - low) / 2);

        result = _bt_compare(rel, key, page, mid);

        if (result >= cmp) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    //todo
    if (P_ISLEAF(special)) {
        return low;
    }

    // todo;
    return OffsetNumberPrev(low);
}

bool _bt_first(IndexScanDesc scan) {
    // bin_srch the point
    BTStack stack = NULL;
    BlockNum blkno;
    OffsetNumber offset;
    Buffer buf;
    
    BTreeScan itup_key = palloc(sizeof(BTreeScanData));
    itup_key->itup = palloc(sizeof(IndexTupleData));
    itup_key->itup->key = scan->key;
    itup_key->itemsz = sizeof(IndexTupleData);
    // todo: for equal stratgy, nextkey is false;
    // will do more job
    itup_key->nextkey = false;
    itup_key->keysz = 1;
    itup_key->scankeys[0].sk_data = scan->key;
    itup_key->scankeys[0].sk_comp = int_cmp;
    stack = _bt_search(scan->index_rel, itup_key, &buf);

    Page page = BufferGetPage(buf);
    BufferDesc* desc = GetBufferDesc(buf);
    offset = _bt_findinsertloc(scan->index_rel, buf, itup_key);
    scan->block = desc->tag.blockNum;
    scan->offset = offset;

    Item item = PageGetItem(page, PageGetItemId(page, offset));

    IndexTuple itup = (IndexTuple)item;
    scan->value = itup->value;

    pfree(itup_key->itup);
    pfree(itup_key);
    
    _bt_freestack(stack);
    return true;
}

bool _bt_next(IndexScanDesc scan) {
    Page page;
    Buffer buf;
    Relation rel = scan->index_rel;
    BlockNum blkno = scan->block;
    OffsetNumber offset = scan->offset;

    buf = _bt_get_buf(rel, blkno);
    page = BufferGetPage(buf);
    OffsetNumber limit = PageGetMaxOffsetNumber(page);
    offset = OffsetNumberNext(offset);
    if (offset > limit) {
        // for now , skip to jump to next page.
        return false;
    }
    ItemId itemid = PageGetItemId(page, offset);
    Item item = PageGetItem(page, itemid);
    IndexTuple itup = (IndexTuple)item;
    if (itup->key == scan->key) {
        scan->value = itup->value;
        scan->offset = offset;
        return true;
    }

    return false;
}