#include "../g.hpp"

#include "access/relpath.h"

TEST(Common, relpath_main) {
    char* path = GetRelPath(1, 1, ForkNumber::MAIN_FORKNUM);
    EXPECT_STREQ("1_1_main", path);
    pfree(path);
}

TEST(Common, relpath_fsm) {
    char* path = GetRelPath(1, 1, ForkNumber::FSM_FORKNUM);
    EXPECT_STREQ("1_1_fsm", path);
    pfree(path);
}
