#include "util/sysdbg.h"
#include "storage/page.h"
#include "storage/bufmgr.h"
#include "access/btree.h"

static void pprint(Relation rel, Page page);

void
pprint(Relation rel, Page page) {

    PageHeader header    = PageGetHeader(page);
    BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);

    int max = PageGetMaxOffsetNumber(page);

    printf("Root page itemsz: %d , %d , %d \r\n", max, special->btsd_flags, special->btsd.level);
    for (int i = P_FIRSTDATAKEY(special); i <= max; i++) {
        struct ItemIdData item = header->pd_linp[i - 1];
        if (P_ISLEAF(special)) {
            IndexTuple tuple = (IndexTuple)(PageGetItem(page, PageGetItemId(page, i)));

           // printf("Leaf    index: %d , off: %d , len: %d , key: %d , value: %d \r\n", i, item.lp_off, item.lp_len,
             //      tuple->key, tuple->t_tid.ip_blkno);
        } else {
            IndexTuple tuple = (IndexTuple)(PageGetItem(page, PageGetItemId(page, i)));

           // printf("No-leaf index: %d , off: %d , len: %d , key: %d , blkno: %d\r\n", i, item.lp_off, item.lp_len,
             //      tuple->key, tuple->value);
            BlockNumber blkno = tuple->t_tid.ip_blkno;
            // Buffer buf = _bt_get_buf(rel, blkno);
            // Page p2 = BufferGetPage(buf);
            // pprint(rel, p2);
        }
    }
}
