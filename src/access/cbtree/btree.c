#include "access/btree.h"
#include "util/mctx.h"
#include "storage/indexfsm.h"
#include "storage/buf_internals.h"

void btbuildempty(Relation rel) {

}
bool btinsert(Relation rel, int key, int value) {
    bool result;
    IndexTuple tup;

    tup = _bt_make_tuple(key, value);

    result = _bt_do_insert(rel, tup);

    pfree(tup);

    return result;
}
bool btremove(Relation rel, int key) {
    return false;
}
bool btgettuple(Relation rel, int key, int* value) {
    *value = key * 10;
    return true;
}

Buffer _bt_get_root(Relation rel) {
    Buffer buf;
    BlockNum blkno = rel->root_blkno;
    if (blkno == P_NEW) {
        // init new page;
        Buffer root = _bt_get_buf(rel, P_NEW);
        Page page = BufferGetPage(root);
        _bt_init_page(page);
        BTreeSpecial special = (BTreeSpecial)PageGetSpecial(root);
        special->flags = BTP_ROOT | BTP_LEAF;

        rel->root_blkno = GetBufferDesc(root)->tag.blockNum;
        blkno = rel->root_blkno;
        ReleaseBuffer(root);
    }

    buf = _bt_get_buf(rel, blkno);
    return buf;
}

Buffer _bt_get_buf(Relation rel, BlockNum blkno) {
    Buffer buf;
    if (blkno != P_NEW) {
        buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
    }
    else {
        // create new block for cbtree
        blkno = GetFreeIndexPage(rel);
        buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
        Page page = BufferGetPage(buf);
        _bt_init_page(page);
    }
    return buf;
}

void _bt_init_page(Page page) {
    PageInit(page, BLKSZ, sizeof(BTreeSpecialData));
}

Buffer _bt_moveright(Relation rel, IndexTuple itup, Buffer buf) {
    return 0;
}