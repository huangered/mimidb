#include "access/btree.hpp"

// refact
OffsetNumber BtreeIndex::_bt_find_split_offset(Buffer buf) {
    // use half for simple
    Page page = _bufMgr->GetPage(buf);
    OffsetNumber offset = PageGetMaxOffsetNumber(page);
    return offset / 2;
}

OffsetNumber BtreeIndex::_bt_findinsertloc(Relation rel, Buffer buffer, BTreeScan key) {
    Page page = _bufMgr->GetPage(buffer);

    OffsetNumber offset = _bt_binsrch(rel, page, key);

    return offset;
}