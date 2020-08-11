#ifndef _HASH_H_
#define _HASH_H_

#include "c.h"

typedef uint32 (*HashValueFunc)(const void* key, Size keysize);
typedef bool (*HashEqualFunc)(const void* left, const void* right, Size keysize);

/*
structure layout:
-  next ptr
- key region
- value region
*/
typedef struct HashElem {
    struct HashElem* next;
} HashElem;



typedef struct HashSegment {
    HashElem* next;
} HashSegment;

typedef struct Hash {
    long        num_partitions;
    Size        keysize;
    Size        entrysize;
    HashValueFunc hash;
    HashEqualFunc equal;
    HashSegment* list;
    const char* name;
} Hash;

typedef enum HashAction {
    Add,
    Remove,
    Search,
} HashAction;

#define GetEntryKey(tbl, elem)   (char*)((char*)elem + sizeof(HashElem))
#define GetEntryValue(tbl, elem)   (char*)((char*)elem + sizeof(HashElem) + tbl->keysize)

extern Hash* hash_create(const char* name, HashValueFunc hash, HashEqualFunc equal, Size keysize, Size entrysize);
extern void hash_destroy(Hash* tbl);
extern void* hash_search(Hash* tbl, HashAction action, const void* key);

// string hash func
static uint32 string_hash(const void* key, Size keysize) {
    //char* first = (char*)key;
    //return *first;
    return 0;
}
// string equal func
static bool string_equal(const void* left, const void* right, Size keysize) {
    char* l = (char*)left;
    char* r = (char*)right;
    for (int i = 0; i < keysize; i++) {
        if (*(l + i) != *(r + i)) {
            return false;
        }
    }
    return true;
}


#endif // !_HASH_H
