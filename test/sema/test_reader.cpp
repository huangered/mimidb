#include "../g.hpp"
#include "sema/test.hpp"
#include "sema/sema.hpp"

#ifdef _WIN32

TEST(Sema, reader) {

    const char* str = "select * from asdf;";
    Node n          = raw_parse(str);

    EXPECT_EQ(n != nullptr, true);

    delete n;
}

#endif