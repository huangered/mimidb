#include "access/btree.h"
#include "access/rel.h"
#include "storage/page.h"

OffsetNumber
_bt_binsrch(Relation rel, Page page, BTreeScan key) {
    int result;

    BTreeSpecial special = PageGetSpecial(page);
    int low              = P_FIRSTDATAKEY(special);
    int high             = PageGetMaxOffsetNumber(page);

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
        } else {
            high = mid;
        }
    }

    // todo
    if (P_ISLEAF(special)) {
        return low;
    }

    // todo;
    return OffsetNumberPrev(low);
}

bool
_bt_first(IndexScanDesc scan) {
    // bin_srch the point
    BTStack stack;

    OffsetNumber offset;
    Buffer buf;

    IndexTuple itup = palloc(sizeof(IndexTupleData));
    itup->t_info    = sizeof(IndexTupleData);

    BTreeScan itup_key = _bt_make_scankey(scan->index_rel, itup);
    stack              = _bt_search(scan->index_rel, itup_key, &buf);

    struct BufferDesc* desc = GetBufferDescriptor(buf);
    Page page               = BufferGetPage(buf);
    itup_key->nextkey       = false;
    offset                  = _bt_binsrch(scan->index_rel, page, itup_key);

    scan->block  = desc->tag.blockNum;
    scan->offset = offset;

    Item item = PageGetItem(page, PageGetItemId(page, offset));

    IndexTuple itup1 = (IndexTuple)item;
    //scan->value      = itup1->value;

    pfree(itup);
    pfree(itup_key);

    _bt_freestack(stack);
    return true;
}

bool
_bt_next(IndexScanDesc scan) {
    Page page;
    Buffer buf;
    Relation rel        = scan->index_rel;
    BlockNumber blkno   = scan->block;
    OffsetNumber offset = scan->offset;

    buf                = _bt_get_buf(rel, blkno);
    page               = BufferGetPage(buf);
    OffsetNumber limit = PageGetMaxOffsetNumber(page);
    offset             = OffsetNumberNext(offset);
    if (offset > limit) {
        // for now , skip to jump to next page.
        return false;
    }
    ItemId itemid   = PageGetItemId(page, offset);
    Item item       = PageGetItem(page, itemid);
    IndexTuple itup = (IndexTuple)item;
    //if (itup->key == scan->key) {
    //    scan->value  = itup->value;
    //    scan->offset = offset;
    //    return true;
    //}

    return false;
}

int
_bt_compare(Relation rel, BTreeScan key, Page page, OffsetNumber offset) {

    int keysz;
    ScanKey skey;

    ItemId itemId = PageGetItemId(page, offset);

    BTreeSpecial special = PageGetSpecial(page);

    if (!P_ISLEAF(special) && offset == P_FIRSTDATAKEY(special)) {
        return 1;
    }

    IndexTuple itup = (IndexTuple)PageGetItem(page, itemId);

    keysz = key->keysz;
    skey  = key->scankeys;

    for (int i = 0; i < keysz; i++) {

        struct FmgrInfo info = skey->sk_func;

//        Datum result = DirectFunctionCall2Coll(info.fn_method, key->itup->key, itup->key);

        int r;//        = DatumGetInt(result);

        if (r != 0) {
            return r;
        }
    }

    return 0;
}
