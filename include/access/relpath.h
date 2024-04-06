#ifndef _relpath_hpp_
#define _relpath_hpp_

#include "mimi.h"

typedef enum ForkNumber {
    MAIN_FORKNUM = 0,
    FSM_FORKNUM,
    INIT_FORKNUM,
    NUMS_FORKNUM,
} ForkNumber;

extern char* GetRelPath(Oid dbNode, Oid relNode, ForkNumber fn);

#endif // !_relpath_h_
