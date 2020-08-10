#include "access/btree.h"
#include "util/mctx.h"

BTreeInsert _bt_make_scankey(Relation rel, IndexTuple itup) {
    BTreeInsert key = palloc(sizeof(BTreeInsertData));
    key->itup = itup;
    key->itemsz = sizeof(IndexTupleData);
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