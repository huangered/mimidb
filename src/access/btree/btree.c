#include "access/btree.h"
#include "util/mctx.h"
#include "storage/indexfsm.h"

static const IndexAmRoute route = {
    .ambuildempty = btbuildempty,
    .aminsert = btinsert,
    .amremove = btremove,
    .amgettuple = btgettuple,
    .amvacuum = btvacuum
};

IndexAmRoute* buildRoute() {
    return &route;
}

void btbuildempty(Relation rel) {
    Page metap = palloc(BLKSZ);
    _bt_init_page(metap);

    BTreeMetaData* metad = (BTreeMetaData*)PageGetContent(metap);
    metad->root = P_NONE;

    // write to local file system
    Buffer buf = ReadBuffer(rel, MAIN_FORKNUM, BTREE_METAPAGE);
    Page page = BufferGetPage(buf);
    memcpy(page, metap, BLKSZ);
    pfree(metap);
}

bool btinsert(Relation rel, int key, int ht_id) {
    bool result;
    IndexTuple tup;

    tup = _bt_make_tuple(key, ht_id);

    result = _bt_do_insert(rel, tup);

    pfree(tup);

    return result;
}
bool btremove(Relation rel, int key) {
    return false;
}
bool btgettuple(IndexScanDesc scan) {

    if (scan->block == INVALID_BLOCK) {
        return _bt_first(scan);
    }
    else {
        return _bt_next(scan);
    }
}


void _bt_init_page(Page page) {
    PageInit(page, BLKSZ, sizeof(BTreeSpecialData));
    BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);
    special->level = 0;
    special->block_prev = INVALID_BLOCK;
    special->block_next = INVALID_BLOCK;
    special->flags = P_NONE;
}

Buffer _bt_moveright(Relation rel, BTreeScan key, Buffer buf) {
    for (;;) {
        Page page = BufferGetPage(buf);
        PageHeader header = PageGetHeader(page);
        BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);

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

Buffer _bt_relandgetbuf(Relation rel, Buffer obuf, BlockNumber blkno) {
    ReleaseBuffer(obuf);
    Buffer buffer = ReadBuffer(rel, MAIN_FORKNUM, blkno);
    return buffer;
}
