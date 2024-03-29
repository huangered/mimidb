#include "../g.hpp"

#include "util/fmgr.hpp"
#include "util/builtins.hpp"

TEST(hash_fmgr, basic_int) {
    int r = DirectFunctionCall2Coll(int8cmp, 1, 2);
    EXPECT_EQ(r, -1);
}

TEST(hash_fmgr, find) {
    FmgrInfo info;
    fmgr_info(INT8CMP_OID, &info);
    EXPECT_EQ(info.fn_id, INT8CMP_OID);
}
