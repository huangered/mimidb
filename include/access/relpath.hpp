#ifndef _RELPATH_H_
#define _RELPATH_H_

#include <filesystem>
#include "mimi.hpp"

typedef enum ForkNumber {
    MAIN_FORKNUM = 0,
    FSM_FORKNUM,
    INIT_FORKNUM,
} ForkNumber;

std::filesystem::path GetRelPath2(Oid dbNode, Oid relNode, ForkNumber fn);

#endif // !_relpath_h_
