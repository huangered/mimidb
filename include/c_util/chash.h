#ifndef _chash_h_
#define _chash_h_

#include <stdbool.h>

typedef int (*hash_hasher)(void*);
typedef bool (*hash_comparator)(void* , void* );

typedef struct hash_elem {
  struct hash_elem* next;
  void* key;
  void* value;
} hash_elem;

typedef struct hash_table {
  hash_hasher hasher;
  hash_comparator cmp;
  
  int nbuckets;
  hash_elem* buckets;
} hash_table;

hash_table* hash_init(int num, hash_hasher hasher, hash_comparator cmp); 
void hash_put(hash_table* tbl, void* key, void* value);
bool hash_get(hash_table* tbl, void* key, void** value);

#endif
