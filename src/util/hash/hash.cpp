#include "c.hpp"
#include "util/hash.hpp"
#include "util/mctx.hpp"

#define NUM_PARTITIONS 8

static HashElem* _search_elem(HashElem** elem, const void* key, Hash* tbl);
static HashElem* _search_elem_or_add(HashElem** elem, const void* key, Hash* tbl);
static void _remove_elem(HashElem** elem, const void* key, Hash* tbl);

Hash* hash_create(const char* name, HashValueFunc hash, HashEqualFunc equal, Size keysize, Size entrysize) {
    Hash* tbl = (Hash*)palloc(sizeof(Hash));
    tbl->name = (char*)palloc(strlen(name) + 1);
    strcpy(tbl->name, name);
    tbl->hash = hash;
    tbl->equal = equal;
    tbl->num_partitions = NUM_PARTITIONS;
    tbl->keysize = keysize;
    tbl->entrysize = entrysize;
    tbl->list = (HashSegment*)palloc(NUM_PARTITIONS * sizeof(HashSegment));
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
            pfree(cur);
        }
    }
    pfree(tbl->list);
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
    case Remove:
        _remove_elem(&tbl->list[segment].next, key, tbl);
        break;
    default:
        break;
    }

    return result == NULL ? NULL : GetEntryValue(tbl, result);
}

HashElem* _search_elem(HashElem** he, const void* key, Hash* tbl) {
    for (; *he != NULL;) {
        void* k2 = GetEntryKey(tbl, *he);
        if (tbl->equal(k2, key, tbl->keysize)) {
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
        void* key1 = GetEntryKey(tbl, he);
        if (tbl->equal(key1, key, tbl->keysize)) {
            return *he;
        }
        else {
            he = &(*he)->next;
        }
    }
    HashElem* result = (HashElem*)palloc(sizeof(HashElem) + tbl->keysize + tbl->entrysize);
    result->next = NULL;
    memcpy(GetEntryKey(tbl, result), key, tbl->keysize);
    memset(GetEntryValue(tbl, result), 0, tbl->entrysize);

    *he = result;

    return result;
}

static void _remove_elem(HashElem** elem, const void* key, Hash* tbl) {
    for (; *elem != NULL;) {
        HashElem* el = *elem;
        void* k2 = GetEntryKey(tbl, el);
        if (tbl->equal(k2, key, tbl->keysize)) {
            *elem = el->next;
            pfree(el);
        }
        else {
            elem = &el->next;
        }
    }
}