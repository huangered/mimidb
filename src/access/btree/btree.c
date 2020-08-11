#include "access/btree.h"
#include "util/mctx.h"
#include "storage/indexfsm.h"


void btbuildempty(Relation rel) {
    Page metap = palloc(BLKSZ);
    _bt_init_page(metap);

    BTreeMetaData* metad = PageGetContent(metap);
    metad->root = P_NONE;

    // write to local file system
    Buffer buf = ReadBuffer(rel, MAIN_FORKNUMBER, BTREE_METAPAGE);
    Page page = BufferGetPage(buf);
    memcpy(page, metap, BLKSZ);
    pfree(metap);
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

    BTreeSearchKey skey = NULL;

    if (key == 0) {
        _bt_first(skey);
    }
    else {
        _bt_next(skey);
    }

    return true;
}


void _bt_init_page(Page page) {
    PageInit(page, BLKSZ, sizeof(BTreeSpecialData));
    BTreeSpecial special = PageGetSpecial(page);
    special->level = 0;
    special->block_prev = INVALID_BLOCK;
    special->block_next = INVALID_BLOCK;
    special->flags = P_NONE;
}

Buffer _bt_moveright(Relation rel, BTreeInsert key, Buffer buf) {
    for (;;) {
        Page page = BufferGetPage(buf);
        PageHeader header = PageGetHeader(page);
        BTreeSpecial special = PageGetSpecial(page);

        if (P_RIGHTMOST(special)) {
            break;
        }
        
        if (_bt_compare(rel, key, page, P_HIKEY) >= 0) {
            buf = _bt_relandgetbuf(rel, buf, special->block_next);
            continue;
        }
        else {
            break;
        }
    }
    return buf;
}

Buffer _bt_relandgetbuf(Relation rel, Buffer obuf, BlockNum blkno) {
    ReleaseBuffer(obuf);
    Buffer buffer = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
    return buffer;
}