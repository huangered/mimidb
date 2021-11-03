#include "access/btree.hpp"
#include "storage/freespace.hpp"
#include "util/mctx.hpp"

static BtreeIndex btree{};

IndexAm*
BtreeRoute() {
    return &btree;
}

BtreeIndex::BtreeIndex() {
}

void
BtreeIndex::BuildEmpty(Relation rel) {
    Page metap = (Page)palloc(BLKSZ);
    _bt_init_page(metap);

    // write to local file system
    smgr->Write(rel->rd_smgr, MAIN_FORKNUM, BTREE_METAPAGE, metap);

    pfree(metap);
}

bool
BtreeIndex::Insert(Relation rel, int key, int ht_id) {
    bool result;
    IndexTuple tup;

    tup = _bt_make_tuple(key, ht_id);

    result = _bt_do_insert(rel, tup, UNIQUE_CHECK_YES, nullptr);

    delete tup;

    return result;
}
bool
BtreeIndex::Remove(Relation rel, int key) {
    return false;
}
bool
BtreeIndex::GetNext(IndexScanDesc scan, ScanDirection dir) {

    if (scan->block == INVALID_BLOCK) {
        return _bt_first(scan);
    } else {
        return _bt_next(scan);
    }
}

IndexScanDesc
BtreeIndex::BeginScan(Relation nrel, int nkeys, ScanKey key) {
    return nullptr;
}
void
BtreeIndex::EndScan(Relation rel, int nkeys) {
    // todo
}

// private method

void
BtreeIndex::_bt_init_metapage(Page page, BlockNumber rootblkno) {
    _bt_init_page(page);
    BTreeMetaData* metad = (BTreeMetaData*)PageGetContent(page);
    metad->fastroot      = P_NONE;
}

void
BtreeIndex::_bt_init_page(Page page) {
    PageInit(page, BLKSZ, sizeof(BTreeSpecialData));
}

Buffer
BtreeIndex::_bt_moveright(Relation rel, BTreeScan key, Buffer buf) {
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
BtreeIndex::_bt_relandgetbuf(Relation rel, Buffer obuf, BlockNumber blkno) {
    ReleaseBuffer(obuf);
    Buffer buffer = ReadBuffer(rel, blkno);
    return buffer;
}

void
BtreeIndex::debug(Relation rel) {
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
