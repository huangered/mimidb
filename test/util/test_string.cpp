#include "../g.hpp"

#include "util/string.hpp"

TEST(string_test, basic_int)
{
    yih::String a{ "abcd" };
    yih::String b{ a };
}