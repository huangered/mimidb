#ifndef _HASH_H_
#define _HASH_H_

#include "c.h"

typedef uint32 (*HashValueFunc)(const void* key, Size keysize);

typedef struct HashElem {
    int key;
    int value;
    struct HashElem* next;
} HashElem;

typedef struct Hash {
    HashValueFunc hash;
    HashElem* list;
} Hash;

extern Hash* hash_create();
extern void hash_search(Hash* tbl, const void* key);

#endif // !_HASH_H
