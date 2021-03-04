#include "../g.hpp"


#include "util/hashmap.hpp"


TEST(hash_test, add)
{
    HashMap<int, int> a;
    for (int i{}; i < 100; i++) {
        a.Put(i, i);
    }

    int v{ -99 };
    EXPECT_TRUE(a.Get(1, &v));
    EXPECT_EQ(v, 1);
    
    a.Remove(1);

    EXPECT_FALSE(a.Get(1, &v));
}