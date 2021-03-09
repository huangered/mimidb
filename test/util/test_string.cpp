#include "../g.hpp"

#include "util/string.hpp"

TEST(string_test, basic_int)
{
    yih::String a{ "abcd" };
    EXPECT_EQ(a.Len(), 4);

    yih::String b{ a };
    EXPECT_EQ(b.Len(), 4);

    a.Append("efg");
    EXPECT_EQ(a.Len(), 7);

    a.Append("");
    EXPECT_EQ(a.Len(), 7);
}