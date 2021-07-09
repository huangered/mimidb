#include "access/btree.hpp"

/*
make a scan key
*/
BTreeScan
BtreeIndex::_bt_make_scankey(Relation rel, IndexTuple itup) {
    int nkeys = 1;
    ScanKey skey;

    BTreeScan key = new BTreeScanData(nkeys);
    key->itup = itup;
    key->itemsz = sizeof(IndexTupleData);
    key->nextkey = false;
    key->keysz = nkeys;

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
BtreeIndex::_bt_make_tuple(int key, int ht_id) {
    IndexTuple tup = new IndexTupleData{};
    tup->key = key;
    tup->ht_id = ht_id;
    tup->tuple_size = sizeof(IndexTupleData);
    return tup;
}

/*
free the tree stack
*/
void
BtreeIndex::_bt_freestack(BTStack stack) {
    while (stack != nullptr) {
        BTStack parent = stack->parent;
        delete stack;
        stack = parent;
    }
}