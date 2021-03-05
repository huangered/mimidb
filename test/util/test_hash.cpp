#include "../g.hpp"

#include "util/hashmap.hpp"

TEST(hash_test, basic_int)
{
    HashMap<int, int> map;
    for (int i{}; i < 100; i++) {
        map.Put(i, i);
    }

    int v{ -99 };
    EXPECT_TRUE(map.Get(1, &v));
    EXPECT_EQ(v, 1);
    
    map.Remove(1);

    EXPECT_FALSE(map.Get(1, &v));
}