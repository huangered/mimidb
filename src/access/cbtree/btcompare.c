#include "access/btree.h"

int _bt_compare(Relation rel, BTreeInsert key, Page page, OffsetNumber offset) {
    ItemId itemId = PageGetItemId(page, offset);

    BTreeSpecial special = PageGetSpecial(page);

    if (!P_ISLEAF(special) && offset == P_FIRSTDATAKEY(special)) {
        return 1;
    }

    IndexTuple itup = (IndexTuple)PageGetItem(page, itemId);

    return memcmp(key->itup, itup, key->itemsz);
}