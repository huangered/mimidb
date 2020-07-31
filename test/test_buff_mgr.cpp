#include <gtest/gtest.h>

_EXTERN_C
#include "storage/bufmgr.h"
#include "util/mctx.h"
_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(hash_buff_mgr, basic)
{
    Relation rel = (Relation)palloc(sizeof(Relation));
    rel->rnode = 1;
    BufferInit();

    Buffer buf_id = ReadBuffer(rel, ForkNumber::MAIN_FORKNUMBER, 0);

    EXPECT_EQ(buf_id, 0);

    buf_id = ReadBuffer(rel, ForkNumber::MAIN_FORKNUMBER, 0);

    EXPECT_EQ(buf_id, 0);


    ReleaseBuffer(buf_id);
    ReleaseBuffer(buf_id);
}