#include "access/btree.h"
#include "util/mctx.h"

BTreeScan _bt_make_scankey(Relation rel, IndexTuple itup) {
    BTreeScan key = palloc(sizeof(BTreeScanData));
    key->itup = itup;
    key->itemsz = sizeof(IndexTupleData);
    key->nextkey = false;
    key->keysz = 1;
    key->scankeys[0].sk_data = itup->key;
    key->scankeys[0].sk_comp = int_cmp;
    return key;
}

IndexTuple _bt_make_tuple(int key, int value) {
    IndexTuple tup = palloc(sizeof(IndexTupleData));
    tup->key = key;
    tup->value = value;
    tup->ctid = 0;
    return tup;
}

void _bt_freestack(BTStack stack) {
    while (stack != NULL) {
        BTStack parent = stack->parent;
        pfree(stack);
        stack = parent;
    }
}