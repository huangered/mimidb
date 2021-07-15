#include "../g.hpp"

#include "sema/dictionary.hpp"

TEST(dictionary_test, basic) {
    int* q = new int{3};
    Dictionary<int, int, int*> a1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            a1.put(i, j, new int{3});
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            auto q = a1.get(i, j);
            EXPECT_EQ(*q.second, 3);
        }
    }

    auto q123 = a1.get(100, 100);
    EXPECT_FALSE(q123.first);

    delete q;
}
