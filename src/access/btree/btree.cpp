#include "access/btree.hpp"
#include "storage/indexfsm.hpp"

BtreeIndex::BtreeIndex(std::shared_ptr<BufferMgr> mgr) {
    _bufMgr = mgr;
}

void
BtreeIndex::buildempty(Relation rel) {
    Page metap = new char[BLKSZ];
    _bt_init_page(metap);

    BTreeMetaData* metad = (BTreeMetaData*)PageGetContent(metap);
    metad->root = P_NONE;

    // write to local file system
    Buffer buf = _bufMgr->ReadBuffer(rel, MAIN_FORKNUM, BTREE_METAPAGE);
    Page page = _bufMgr->GetPage(buf);
    memcpy(page, metap, BLKSZ);
    delete metap;
}

bool
BtreeIndex::insert(Relation rel, int key, int ht_id) {
    bool result;
    IndexTuple tup;

    tup = _bt_make_tuple(key, ht_id);

    result = _bt_do_insert(rel, tup);

    delete tup;

    return result;
}
bool
BtreeIndex::remove(Relation rel, int key) {
    return false;
}
bool
BtreeIndex::gettuple(IndexScanDesc scan) {

    if (scan->block == INVALID_BLOCK) {
        return _bt_first(scan);
    }
    else {
        return _bt_next(scan);
    }
}

// private method

void
BtreeIndex::_bt_init_page(Page page) {
    PageInit(page, BLKSZ, sizeof(BTreeSpecialData));
    BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);
    special->level = 0;
    special->block_prev = INVALID_BLOCK;
    special->block_next = INVALID_BLOCK;
    special->flags = P_NONE;
}

Buffer
BtreeIndex::_bt_moveright(Relation rel, BTreeScan key, Buffer buf) {
    for (;;) {
        Page page = _bufMgr->GetPage(buf);
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

Buffer
BtreeIndex::_bt_relandgetbuf(Relation rel, Buffer obuf, BlockNumber blkno) {
    _bufMgr->ReleaseBuffer(obuf);
    Buffer buffer = _bufMgr->ReadBuffer(rel, MAIN_FORKNUM, blkno);
    return buffer;
}
