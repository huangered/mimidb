#include "util/hash.h"
#include "c.h"
#include "util/mctx.h"

Hash* hash_create(const char* name, HashValueFunc hash, HashEqualFunc equal, Size keysize) {
    Hash* tbl = palloc(sizeof(Hash));
    tbl->name = palloc(strlen(name)+1);
    strcpy(tbl->name, name);
    tbl->hash = hash;
    tbl->equal = equal;
    tbl->num_partitions = 8;
    tbl->keysize = keysize;
    tbl->entrysize = 0;
    tbl->list = palloc(8 * sizeof(HashSegment));
    memset(tbl->list, 0, 8 * sizeof(HashSegment));
    return tbl;
}

void hash_destroy(Hash* tbl) {
    pfree(tbl->name);
    for (int i = 0; i < 8; i++) {
        HashElem* he = tbl->list[i].next;
        for (; he != NULL;) {
            HashElem* cur = he;
            he = he->next;
            free(cur);
        }
    }
    pfree(tbl);
}

void* hash_search(Hash* tbl, HashAction action, const void* key) {

    uint32 hashValue = tbl->hash(key, tbl->keysize);
    int segment = hashValue % 8;
    HashElem* he = tbl->list[segment].next;
    for (; he != NULL;) {
        if (tbl->equal(he->key, key, tbl->keysize)) {
            return he->value;
        }
        else {
            he = he->next;
        }
    }
    return NULL;
}