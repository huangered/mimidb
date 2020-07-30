#include "c.h"
#include "util/hash.h"
#include "util/mctx.h"

#define NUM_PARTITIONS 8

static HashElem* _search_elem(HashElem** elem, const void* key, Hash* tbl);
static HashElem* _search_elem_or_add(HashElem** elem, const void* key, Hash* tbl);

Hash* hash_create(const char* name, HashValueFunc hash, HashEqualFunc equal, Size keysize, Size entrysize) {
    Hash* tbl = palloc(sizeof(Hash));
    tbl->name = palloc(strlen(name) + 1);
    strcpy(tbl->name, name);
    tbl->hash = hash;
    tbl->equal = equal;
    tbl->num_partitions = NUM_PARTITIONS;
    tbl->keysize = keysize;
    tbl->entrysize = entrysize;
    tbl->list = palloc(NUM_PARTITIONS * sizeof(HashSegment));
    memset(tbl->list, 0, NUM_PARTITIONS * sizeof(HashSegment));
    return tbl;
}

void hash_destroy(Hash* tbl) {
    pfree(tbl->name);
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        HashElem* he = tbl->list[i].next;
        for (; he != NULL;) {
            HashElem* cur = he;
            he = he->next;
            pfree(cur->key);
            pfree(cur->value);
            pfree(cur);
        }
    }
    pfree(tbl);
}

void* hash_search(Hash* tbl, HashAction action, const void* key) {
    HashElem* result = NULL;

    uint32 hashValue = tbl->hash(key, tbl->keysize);
    int segment = hashValue % NUM_PARTITIONS;
    
    switch (action) {
    case Search:
        result = _search_elem(&tbl->list[segment].next, key, tbl);
        break;
    case Add:
        result = _search_elem_or_add(&tbl->list[segment].next, key, tbl);
        break;
    default:
        break;
    }

    return result == NULL ? NULL : result->value;
}

HashElem* _search_elem(HashElem** he, const void* key, Hash* tbl) {
    for (; *he != NULL;) {
        if (tbl->equal( (*he)->key, key, tbl->keysize)) {
            return *he;
        }
        else {
            he = &(*he)->next;
        }
    }
    return NULL;
}


static HashElem* _search_elem_or_add(HashElem** he, const void* key, Hash* tbl) {
    for (; *he != NULL;) {
        if (tbl->equal((*he)->key, key, tbl->keysize)) {
            return *he;
        }
        else {
            he = &(*he)->next;
        }
    }
    HashElem* result = palloc(sizeof(HashElem));
    result->key = palloc(tbl->keysize);
    memcpy(result->key, key, tbl->keysize);
    result->value = palloc(tbl->entrysize);
    memset(result->value, 0, tbl->entrysize);
    result->next = NULL;
    *he = result;
    
    return result;
}