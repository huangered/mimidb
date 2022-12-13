#include "access/btree.h"

/*
make a scan key
*/
BTreeScan
_bt_make_scankey(Relation rel, IndexTuple itup) {
    int nkeys = 1;
    ScanKey skey;

    BTreeScan key = palloc(sizeof(struct BTreeScanData));
    key->itup     = itup;
    key->itemsz   = sizeof(IndexTupleData);
    key->nextkey  = false;
    key->keysz    = nkeys;

    skey = key->scankeys;

    for (int i = 0; i < nkeys; i++) {
        skey[i].sk_data = itup->key;
        fmgr_info(1, &skey[i].sk_func);
    }
    return key;
}

/*
make a index tuple
*/
IndexTuple
_bt_make_tuple(int key, int ht_id) {
    IndexTuple tup = palloc(sizeof(IndexTupleData));
    tup->key       = key;
    tup->value     = ht_id;
    tup->t_info    = sizeof(IndexTupleData);
    return tup;
}

/*
free the tree stack
*/
void
_bt_freestack(BTStack stack) {
    while (stack != NULL) {
        BTStack parent = stack->parent;
        pfree(stack);
        stack = parent;
    }
}
