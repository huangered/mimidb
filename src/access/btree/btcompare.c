#include "access/btree.h"

int _bt_compare(Relation rel, BTreeScan key, Page page, OffsetNumber offset) {
    ItemId itemId = PageGetItemId(page, offset);

    BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);

    if (!P_ISLEAF(special) && offset == P_FIRSTDATAKEY(special)) {
        return 1;
    }

    IndexTuple itup = (IndexTuple)PageGetItem(page, itemId);

    return key->scankeys[0].sk_comp(itup->key, key->itup->key);
}