#include "access/btree.hpp"
#include "access/rel.hpp"
#include "storage/page.hpp"
#include "util/mctx.hpp"

OffsetNumber BtreeIndex::_bt_binsrch(Relation rel, Page page, BTreeScan key) {
    int result;

    BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);
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

bool BtreeIndex::_bt_first(IndexScanDesc scan) {
    // bin_srch the point
    BTStack stack = NULL;
    
    OffsetNumber offset;
    Buffer buf;
    
    IndexTuple itup = (IndexTuple)palloc(sizeof(IndexTupleData));
    itup->key = scan->key;
    itup->ht_id = scan->value;
    itup->tuple_size = sizeof(IndexTupleData);

    BTreeScan itup_key = _bt_make_scankey(scan->index_rel, itup);
    stack = _bt_search(scan->index_rel, itup_key, &buf);

    BufferDesc* desc = _bufMgr->GetBufferDesc(buf);
    Page page = _bufMgr->GetPage(buf);
    offset = _bt_binsrch(scan->index_rel, page, itup_key);

    scan->block = desc->tag.blockNum;
    scan->offset = offset;

    Item item = PageGetItem(page, PageGetItemId(page, offset));

    IndexTuple itup1 = (IndexTuple)item;
    scan->value = itup1->ht_id;

    pfree(itup);
    pfree(itup_key);
    
    _bt_freestack(stack);
    return true;
}

bool BtreeIndex::_bt_next(IndexScanDesc scan) {
    Page page;
    Buffer buf;
    Relation rel = scan->index_rel;
    BlockNumber blkno = scan->block;
    OffsetNumber offset = scan->offset;

    buf = _bt_get_buf(rel, blkno);
    page = _bufMgr->GetPage(buf);
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
        scan->value = itup->ht_id;
        scan->offset = offset;
        return true;
    }

    return false;
}

int BtreeIndex::_bt_compare(Relation rel, BTreeScan key, Page page, OffsetNumber offset) {

    int keysz;
    ScanKey skey;

    ItemId itemId = PageGetItemId(page, offset);

    BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);

    if (!P_ISLEAF(special) && offset == P_FIRSTDATAKEY(special)) {
        return 1;
    }

    IndexTuple itup = (IndexTuple)PageGetItem(page, itemId);

    keysz = key->keysz;
    skey = key->scankeys;
    
    for (int i = 0; i < keysz; i++) {

        FmgrInfo info = skey->sk_func;

        Datum result = DirectFunctionCall2Coll(info.fn_addr, itup->key, key->itup->key);

        result = DatumGetInt(result);

        if (result != 0) {
            return result;
        }
    }

    return 0;
}