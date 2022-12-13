#include "access/btree.h"
#include "storage/freespace.h"



struct IndexAm*
BtreeRoute() {
    // todo return &btree;
    return NULL;
}

void
BuildEmpty(Relation rel) {
    Page metap = (Page)palloc(BLKSZ);
    _bt_init_page(metap);

    // write to local file system
    //smgr->Write(rel->rd_smgr, MAIN_FORKNUM, BTREE_METAPAGE, metap);

    pfree(metap);
}

bool
Insert(Relation rel, int key, int ht_id) {
    bool result;
    IndexTuple tup;

    tup = _bt_make_tuple(key, ht_id);

    result = _bt_do_insert(rel, tup, UNIQUE_CHECK_YES, NULL);

    pfree(tup);

    return result;
}
bool
Remove(Relation rel, int key) {
    return false;
}
bool
GetNext(IndexScanDesc scan, enum ScanDirection dir) {

    if (scan->block == INVALID_BLOCK) {
        return _bt_first(scan);
    } else {
        return _bt_next(scan);
    }
}

IndexScanDesc
BeginScan(Relation nrel, int nkeys, ScanKey key) {
    return NULL;
}
void
EndScan(Relation rel, int nkeys) {
    // todo
}

// private method

void
_bt_init_metapage(Page page, BlockNumber rootblkno) {
    _bt_init_page(page);
    struct BTreeMetaData* metad = (struct BTreeMetaData*)PageGetContent(page);
    metad->fastroot      = P_NONE;
}

void
_bt_init_page(Page page) {
    PageInit(page, BLKSZ, sizeof(struct BTreeSpecialData));
}

Buffer
_bt_moveright(Relation rel, BTreeScan key, Buffer buf) {
    for (;;) {
        Page page            = BufferGetPage(buf);
        PageHeader header    = PageGetHeader(page);
        BTreeSpecial special = PageGetSpecial(page);

        if (P_RIGHTMOST(special)) {
            break;
        }

        if (_bt_compare(rel, key, page, P_HIKEY) >= 0) {
            buf = _bt_relandgetbuf(rel, buf, special->btsd_next);
            continue;
        } else {
            break;
        }
    }
    return buf;
}

Buffer
_bt_relandgetbuf(Relation rel, Buffer obuf, BlockNumber blkno) {
    ReleaseBuffer(obuf);
    Buffer buffer = ReadBuffer(rel, blkno);
    return buffer;
}

void
debug(Relation rel) {
    Buffer bufp = _bt_get_root(rel);
    Page page   = BufferGetPage(bufp);

    BTreeSpecial special = PageGetSpecial(page);

    while (!P_ISLEAF(special)) {
        OffsetNumber low  = P_FIRSTDATAKEY(special);
        ItemId itemId     = PageGetItemId(page, low);
        Item item         = PageGetItem(page, itemId);
        IndexTuple tuple  = (IndexTuple)item;
        BlockNumber blkno = BTreeTupleGetDownLink(tuple);

        bufp    = ReadBuffer(rel, blkno);
        page    = BufferGetPage(bufp);
        special = PageGetSpecial(page);
    }

    OffsetNumber low  = P_FIRSTDATAKEY(special);
    OffsetNumber high = PageGetMaxOffsetNumber(page);

    for (; low < high; low++) {
        ItemId itemId    = PageGetItemId(page, low);
        Item item        = PageGetItem(page, itemId);
        IndexTuple tuple = (IndexTuple)item;
        printf(">>> %d (%d, %d)\n", tuple->key, tuple->t_tid.ip_blkno, tuple->t_tid.ip_offset);
    }
}
