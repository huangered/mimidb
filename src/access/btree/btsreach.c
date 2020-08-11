#include "access/btree.h"
#include "access/rel.h"

OffsetNumber _bt_binsrch(Relation rel, Page page, BTreeInsert key) {
    int result;

    BTreeSpecial special = PageGetSpecial(page);
    int low = P_FIRSTDATAKEY(special);
    int high = PageGetMaxOffsetNumber(page);

    // for no data item
    if (high < low) {
        return low;
    }

    high++;

    while (low < high) {
        int mid = low + ((high - low) / 2);

        result = _bt_compare(rel, key, page, mid);

        if (result >= 0) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    //todo
    if (P_ISLEAF(special)) {
        return low;
    }

    // todo;
    return low - 1;
}

bool _bt_first(BTreeSearchKey key) {
    return false;
}

bool _bt_next(BTreeSearchKey key) {
    return false;
}