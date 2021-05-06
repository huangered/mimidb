#include "../g.hpp"

#include "access/relpath.hpp"

TEST(Common, relpath_main)
{
    char* path = GetRelPath(1, 1, ForkNumber::MAIN_FORKNUM);
    EXPECT_STREQ("1_1_main", path);
    delete path;
}


TEST(Common, relpath_fsm)
{
    char* path = GetRelPath(1, 1, ForkNumber::FSM_FORKNUM);
    EXPECT_STREQ("1_1_fsm", path);
    delete path;
}

