#include "../g.hpp"

#include "util/string.hpp"

TEST(string_test, basic_int) {
    yih::String a{ "abcd" };
    EXPECT_EQ(a.Len(), 4);

    yih::String b{ a };
    EXPECT_EQ(b.Len(), 4);

    a.Append("efg");
    EXPECT_EQ(a.Len(), 7);

    a.Append("");
    EXPECT_EQ(a.Len(), 7);
}

TEST(string_test, equal) {
    yih::String a{ "abcd" };
    yih::String b{ "abcd" };

    EXPECT_EQ(0, a.Compare(a));
    EXPECT_EQ(0, a.Compare(b));
}

TEST(string_test, not_equal) {
    yih::String a{ "abcd" };
    yih::String b{ "abcd1" };
    yih::String c{ "abce" };

    EXPECT_NE(0, a.Compare(b));
    EXPECT_NE(0, a.Compare(c));
}