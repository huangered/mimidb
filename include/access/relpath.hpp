#ifndef _relpath_hpp_
#define _relpath_hpp_

#include <filesystem>
#include "mimi.hpp"

typedef enum ForkNumber
{
    MAIN_FORKNUM = 0,
    FSM_FORKNUM,
    INIT_FORKNUM,
} ForkNumber;

std::filesystem::path GetRelPath2(Oid dbNode, Oid relNode, ForkNumber fn);

#endif // !_relpath_h_
