#include "g.h"

_EXTERN_C
#include "util/hash.h"
_END_EXTERN_C

TEST(hash_test, add)
{
    int* key = (int*)malloc(sizeof(int));
    *key = 1;

    Hash* tbl = hash_create("test", string_hash, string_equal, 1, 1);
    
    char* value = (char*)hash_search(tbl, Add, key);
    *value = '2';
    value = (char*)hash_search(tbl, Search, key);

    EXPECT_EQ(*value, '2');
    
    hash_destroy(tbl);
}