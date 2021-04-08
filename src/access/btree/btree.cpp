#include "access/btree.hpp"
#include "storage/freespace.hpp"

static BtreeIndex btree{};

IndexAm* BtreeRoute() {
    return &btree;
}

BtreeIndex::BtreeIndex() {
}

void
BtreeIndex::BuildEmpty(Relation rel) {
    Page metap = new char[BLKSZ];
    _bt_init_page(metap);

    // write to local file system
    smgr->Write(rel->rd_smgr, MAIN_FORKNUM, BTREE_METAPAGE, metap);

    delete[] metap;
}

bool
BtreeIndex::Insert(Relation rel, int key, int ht_id) {
    bool result;
    IndexTuple tup;

    tup = _bt_make_tuple(key, ht_id);

    result = _bt_do_insert(rel, tup);

    delete tup;

    return result;
}
bool
BtreeIndex::Remove(Relation rel, int key) {
    return false;
}
bool
BtreeIndex::GetTuple(IndexScanDesc scan) {

    if (scan->block == INVALID_BLOCK) {
        return _bt_first(scan);
    }
    else {
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
    metad->fastroot = P_NONE;
}


void
BtreeIndex::_bt_init_page(Page page) {
    PageInit(page, BLKSZ, sizeof(BTreeSpecialData));
}

Buffer
BtreeIndex::_bt_moveright(Relation rel, BTreeScan key, Buffer buf) {
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

Buffer
BtreeIndex::_bt_relandgetbuf(Relation rel, Buffer obuf, BlockNumber blkno) {
    ReleaseBuffer(obuf);
    Buffer buffer = ReadBuffer(rel, blkno);
    return buffer;
}
