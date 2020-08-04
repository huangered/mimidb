#include "access/btree.h"
#include "access/rel.h"

OffsetNumber _bt_binsrch(Relation rel, Page page, IndexTuple itup) {
    return 0;
}

Buffer _bt_relandgetbuf(Relation rel, Buffer obuf, BlockNum blkno) {
    ReleaseBuffer(obuf);
    Buffer buffer = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
    return buffer;
}
