#include "util/sysdbg.h"
#include "storage/page.h"
#include "storage/bufmgr.h"
#include "access/btree.h"

static void pprint(Relation rel, Page page);

// debug
void debug_rel(Relation rel) {
    Buffer buf = _bt_get_root(rel);
    Page page = BufferGetPage(buf);

    pprint(rel, page);
    ReleaseBuffer(buf);
}

void pprint(Relation rel, Page page) {

    PageHeader header = PageGetHeader(page);
    BTreeSpecial special = PageGetSpecial(page);

    int max = PageGetMaxOffsetNumber(page);

    printf("Root page itemsz: %d , %d , %d \r\n", max, special->flags, special->level);
    for (int i = P_FIRSTDATAKEY(special); i <= max; i++) {
        ItemIdData item = header->pd_linp[i - 1];
        if (P_ISLEAF(special)) {
            IndexTuple tuple = (IndexTuple)(PageGetItem(page, PageGetItemId(page, i)));

            printf("Leaf    index: %d , off: %d , len: %d , key: %d , value: %d \r\n", i, item.lp_off, item.lp_len, tuple->key, tuple->value);
        }
        else {
            IndexTuple tuple = (IndexTuple)(PageGetItem(page, PageGetItemId(page, i)));

            printf("No-leaf index: %d , off: %d , len: %d , key: %d , blkno: %d\r\n", i, item.lp_off, item.lp_len, tuple->key, tuple->value);
            BlockNum blkno = tuple->value;
            Buffer buf = _bt_get_buf(rel, blkno);
            Page p2 = BufferGetPage(buf);
            pprint(rel, p2);
        }
    }
}