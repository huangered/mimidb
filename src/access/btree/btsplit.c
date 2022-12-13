#include "access/btree.h"

// refact
OffsetNumber
BtreeIndex::_bt_find_split_offset(Buffer buf) {
    // use half for simple
    Page page           = BufferGetPage(buf);
    OffsetNumber offset = PageGetMaxOffsetNumber(page);
    return offset / 2;
}

OffsetNumber
BtreeIndex::_bt_findinsertloc(Relation rel, Buffer buffer, BTreeScan key) {
    Page page = BufferGetPage(buffer);

    OffsetNumber offset = _bt_binsrch(rel, page, key);

    return offset;
}