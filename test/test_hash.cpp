#include <gtest/gtest.h>
#include <numeric>
#include <vector>

_EXTERN_C
#include "util/hash.h"
_END_EXTERN_C

TEST(hash_test, basic)
{
    int* key = (int*) malloc(sizeof(int));
    *key = 1;

    Hash* tbl = hash_create("test", string_hash, string_equal, 1);
    tbl->list[1].next = (HashElem*)malloc(sizeof(HashElem));
    tbl->list[1].next->next = NULL;
    tbl->list[1].next->key = key;
    tbl->list[1].next->value = malloc(sizeof(char));
    *((char*)tbl->list[1].next->value) = '1';
    char* value = (char*) hash_search(tbl, Search, key);

    EXPECT_EQ(*value, '1');
    hash_destroy(tbl);
}