#include "../g.hpp"
#include "sema/test.hpp"
TEST(Sema, reader) {

    const char* str = "select * from asdf;";
    Node n          = raw_parse(str);

    EXPECT_EQ(n != nullptr, true);
}