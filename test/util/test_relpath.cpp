#include "../g.hpp"

#include "access/relpath.hpp"

TEST(Common, relpath_main)
{
    auto path = GetRelPath2(1, 1, ForkNumber::MAIN_FORKNUM);
    EXPECT_EQ(std::filesystem::path("1_1_main"), path);
}


TEST(Common, relpath_fsm)
{
    auto path = GetRelPath2(1, 1, ForkNumber::FSM_FORKNUM);
    EXPECT_EQ(std::filesystem::path( "1_1_fsm"), path);
}

