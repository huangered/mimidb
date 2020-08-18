#include "g.h"
_EXTERN_C

#include "access/relpath.h"
#include "util/mctx.h"

_END_EXTERN_C

TEST(Common, relpath_main)
{
    char* path = GetRelPath(1, ForkNumber::MAIN_FORKNUMBER);
    EXPECT_STREQ("1_main", path);
    pfree(path);
}


TEST(Common, relpath_fsm)
{
    char* path = GetRelPath(1, ForkNumber::FSM_FORKNUM);
    EXPECT_STREQ("1_fsm", path);
    pfree(path);
}

