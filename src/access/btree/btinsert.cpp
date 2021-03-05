#include <limits.h>
#include "access/btree.hpp"
#include "util/mctx.hpp"
#include "storage/bufmgr.hpp"


bool BtreeIndex::_bt_do_insert(Relation rel, IndexTuple itup) {
    BTStack stack = NULL;
    bool fastpath = false;
    OffsetNumber newitemoffset;
    Buffer buf;

    BTreeScan itup_key = _bt_make_scankey(rel, itup);

top:
    /*if rel cache buffer */{
        fastpath = false;
    }

    if (!fastpath) {
        stack = _bt_search(rel, itup_key, &buf);
    }

    newitemoffset = _bt_findinsertloc(rel, buf, itup_key);

    _bt_insertonpg(rel, buf, newitemoffset, itup_key, stack);

    _bt_freestack(stack);

    pfree(itup_key);
    _bufMgr->ReleaseBuffer(buf);

    return true;
}

BTStack BtreeIndex::_bt_search(Relation rel, BTreeScan itup_key, Buffer* bufp) {
    BTStack stack_in = NULL;

    *bufp = _bt_get_root(rel);

    for (;;) {
        Page page;
        OffsetNumber offsetnum;
        BlockNumber blkno;
        BlockNumber par_blkno;
        IndexTuple itup;
        ItemId itemid;

        *bufp = _bt_moveright(rel, itup_key, *bufp);

        page = _bufMgr->GetPage(*bufp);

        PageHeader header = PageGetHeader(page);
        BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);

        if (P_ISLEAF(special)) {
            break;
        }

        offsetnum = _bt_binsrch(rel, page, itup_key);
        itemid = PageGetItemId(page, offsetnum);
        itup = (IndexTuple)PageGetItem(page, itemid);
        blkno = BTreeTupleGetDownLink(itup);
        par_blkno = _bufMgr->GetBufferDesc(*bufp)->tag.blockNum;

        BTStack new_stack = (BTStack)palloc(sizeof(BTStackData));
        new_stack->parent = stack_in;
        new_stack->blkno = par_blkno;
        new_stack->offset = offsetnum;
        // read child downstream
        *bufp = _bt_relandgetbuf(rel, *bufp, blkno);

        stack_in = new_stack;
    }

    return stack_in;
}

void BtreeIndex::_bt_insertonpg(Relation rel, Buffer buffer, OffsetNumber newitemoffset, BTreeScan itup_key, BTStack stack) {
    Page page = _bufMgr->GetPage(buffer);

    // size enough
    PageHeader header = PageGetHeader(page);
    BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);
    // if size not enough
    // split and insert into parent
    if (PageGetFreeSpace(page) < itup_key->itemsz) {
        bool is_root = P_ISROOT(special);
        // split and insert into parent;
        Buffer rbuf = _bt_split(rel, itup_key->itup, buffer, newitemoffset);
        _bt_insert_parent(rel, buffer, rbuf, stack, is_root);
        return;
    }

    _bt_addtup(page, itup_key->itup, itup_key->itemsz, newitemoffset);
}

Buffer BtreeIndex::_bt_split(Relation rel, IndexTuple itup, Buffer buf, OffsetNumber newitemoff) {
    OffsetNumber splitoff = _bt_find_split_offset(buf);
    Page originpage = _bufMgr->GetPage(buf);
    Page leftpage = GetTempPage(originpage);
    _bt_init_page(leftpage);
    Buffer rbuf = _bt_get_buf(rel, P_NEW);
    Page rightpage = _bufMgr->GetPage(rbuf);
    _bt_init_page(rightpage);

    BTreeSpecial originspecial = (BTreeSpecial)PageGetSpecial(originpage);
    BTreeSpecial leftspecial = (BTreeSpecial)PageGetSpecial(leftpage);
    BTreeSpecial rightspecial = (BTreeSpecial)PageGetSpecial(rightpage);

    // update right / left point
    leftspecial->block_next = _bufMgr->GetBufferDesc(rbuf)->tag.blockNum;
    rightspecial->block_next = originspecial->block_next;

    leftspecial->block_prev = originspecial->block_prev;
    rightspecial->block_prev = _bufMgr->GetBufferDesc(buf)->tag.blockNum;

    if (P_ISLEAF(originspecial)) {
        leftspecial->flags = BTP_LEAF;
        rightspecial->flags = BTP_LEAF;
    }

    // copy items

    OffsetNumber loffset{ P_FIRSTKEY };
    OffsetNumber roffset;

    if (P_RIGHTMOST(originspecial)) {
        roffset = P_HIKEY;
    }
    else {
        roffset = P_FIRSTKEY;
    }

    // update high key
    ItemId splitItemId = PageGetItemId(originpage, splitoff);
    Item splitItem = PageGetItem(originpage, splitItemId);

    _bt_addtup(leftpage, splitItem, splitItemId->lp_len, P_HIKEY);

    if (!P_RIGHTMOST(originspecial)) {
        ItemId highKeyId = PageGetItemId(originpage, P_HIKEY);
        Item highKey = PageGetItem(originpage, highKeyId);

        _bt_addtup(rightpage, highKey, highKeyId->lp_len, P_HIKEY);

    }

    OffsetNumber i;

    for (i = P_FIRSTDATAKEY(originspecial); i <= PageGetMaxOffsetNumber(originpage); i = OffsetNumberNext(i)) {
        if (i == newitemoff) {
            // insert new item;
            if (i < splitoff) {
                // insert into left
                _bt_addtup(leftpage, itup, sizeof(IndexTupleData), loffset);
                loffset = OffsetNumberNext(loffset);
            }
            else {
                // insert into right;
                _bt_addtup(rightpage, itup, sizeof(IndexTupleData), roffset);
                roffset = OffsetNumberNext(roffset);
            }
        }
        ItemId itemId = PageGetItemId(originpage, i);
        Item item = PageGetItem(originpage, itemId);

        if (i < splitoff) {
            // insert into left
            _bt_addtup(leftpage, item, itemId->lp_len, loffset);
            loffset = OffsetNumberNext(loffset);
        }
        else {
            // insert into right;
            _bt_addtup(rightpage, item, itemId->lp_len, roffset);
            roffset = OffsetNumberNext(roffset);
        }
    }

    if (i <= newitemoff) {
        _bt_addtup(rightpage, itup, sizeof(IndexTupleData), roffset);
    }

    PageRestoreTempPage(leftpage, originpage);
    return rbuf;
}

bool BtreeIndex::_bt_addtup(Page page, Item item, Size itemsz, OffsetNumber newitemoffset) {

    PageAddItem(page, item, itemsz, newitemoffset);

    return true;
}

void BtreeIndex::_bt_insert_parent(Relation rel, Buffer buf, Buffer rbuf, BTStack stack, bool is_root) {
    if (is_root) {
        Buffer rootbuf;

        rootbuf = _bt_newroot(rel, buf, rbuf);
        rel->root_blkno = _bufMgr->GetBufferDesc(rootbuf)->tag.blockNum;
    }
    else {
        Page page = _bufMgr->GetPage(buf);
        IndexTuple ritem = (IndexTuple)PageGetItem(page, PageGetItemId(page, P_HIKEY));
        IndexTuple itup = (IndexTuple)palloc(sizeof(IndexTupleData));
        itup->key = ritem->key;
        itup->ht_id = _bufMgr->GetBufferDesc(rbuf)->tag.blockNum;
        itup->tuple_size = sizeof(IndexTupleData);
        BTreeScan itup_key = _bt_make_scankey(rel, itup);
        Buffer pbuf = _bt_get_buf(rel, stack->blkno);
        _bt_insertonpg(rel, pbuf, stack->offset + 1, itup_key, stack->parent);
        pfree(itup);
        pfree(itup_key);
        _bufMgr->ReleaseBuffer(pbuf);
        _bufMgr->ReleaseBuffer(rbuf);
    }
}



// ?? 
Buffer BtreeIndex::_bt_newroot(Relation rel, Buffer lbuf, Buffer rbuf) {

    // new root buf
    Buffer buf = _bt_get_buf(rel, P_NEW);
    Page rootpage = _bufMgr->GetPage(buf);
    Page lpage = _bufMgr->GetPage(lbuf);
    Page rpage = _bufMgr->GetPage(rbuf);

    _bt_init_page(rootpage);
    PageHeader header = PageGetHeader(rootpage);
    header->pd_flags = BTP_ROOT;
    BTreeSpecial special = (BTreeSpecial)PageGetSpecial(rootpage);
    special->flags = BTP_ROOT;
    special->level = ((BTreeSpecial)PageGetSpecial(lpage))->level + 1;
    // get left page high key
    IndexTuple hkey = (IndexTuple)palloc(sizeof(IndexTupleData));
    hkey->key = INT_MIN;
    hkey->ht_id = _bufMgr->GetBufferDesc(lbuf)->tag.blockNum;
    hkey->tuple_size = sizeof(IndexTupleData);
    // set first item
    _bt_addtup(rootpage, hkey, sizeof(IndexTupleData), P_HIKEY);

    pfree(hkey);
    // set second item
    IndexTuple second;
    IndexTuple lphkey = (IndexTuple)PageGetItem(lpage, PageGetItemId(lpage, P_HIKEY));

    second = (IndexTuple)palloc(sizeof(IndexTupleData));
    second->key = lphkey->key;
    second->ht_id = _bufMgr->GetBufferDesc(rbuf)->tag.blockNum;
    second->tuple_size = sizeof(IndexTupleData);
    _bt_addtup(rootpage, second, sizeof(IndexTupleData), P_FIRSTKEY);

    pfree(second);

    _bufMgr->ReleaseBuffer(rbuf);
    _bufMgr->ReleaseBuffer(buf);
    return buf;
}