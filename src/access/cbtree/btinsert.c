#include "access/btree.h"
#include "util/mctx.h"
#include "storage/bufmgr.h"

IndexTuple _bt_make_tuple(int key, int value) {
    IndexTuple tup = palloc(sizeof(IndexTupleData));
    tup->key = key;
    tup->value = value;
    return tup;
}
bool _bt_do_insert(Relation rel, IndexTuple itup) {
    BTStack stack = NULL;
    bool fastpath = false;
    OffsetNumber newitemoffset;
    Buffer buf;

    BTreeInsert itup_key = _bt_make_scankey(rel, itup);

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
    ReleaseBuffer(buf);

    return true;
}

BTreeInsert _bt_make_scankey(Relation rel, IndexTuple itup) {
    BTreeInsert key = palloc(sizeof(BTreeInsertData));
    key->itup = itup;
    key->itemsz = sizeof(IndexTupleData);
    return key;
}
BTStack _bt_search(Relation rel, BTreeInsert itup_key, Buffer* bufp) {
    BTStack stack_in = NULL;

    *bufp = _bt_get_root(rel);

    for (;;) {
        Page page;
        OffsetNumber offsetnum;
        BlockNum blkno;
        BlockNum par_blkno;
        IndexTuple itup;
        ItemId itemid;

        *bufp = _bt_moveright(rel, itup_key, *bufp);

        page = BufferGetPage(*bufp);

        PageHeader header = PageGetHeader(page);
        BTreeSpecial special = PageGetSpecial(page);

        if (P_ISLEAF(special)) {
            break;
        }

        offsetnum = _bt_binsrch(rel, page, itup_key);
        itemid = PageGetItemId(page, offsetnum);
        itup = PageGetItem(page, itemid);
        blkno = BTreeTupleGetDownLink(itup);
        par_blkno = GetBufferDesc(*bufp)->tag.blockNum;

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
OffsetNumber _bt_findinsertloc(Relation rel, Buffer buffer, BTreeInsert key) {
    return 0;
}
void _bt_insertonpg(Relation rel, Buffer buffer, OffsetNumber newitemoffset, BTreeInsert itup_key, BTStack stack) {
    
}

void _bt_freestack(BTStack stack) {
    while (stack != NULL) {
        BTStack parent = stack->parent;
        pfree(stack);
        stack = parent;
    }
}