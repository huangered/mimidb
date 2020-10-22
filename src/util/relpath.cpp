#include "util/mctx.hpp"
#include "access/relpath.hpp"

const char* const forkNames[] = {
    "main",						/* MAIN_FORKNUM */
    "fsm",						/* FSM_FORKNUM */
};

char* GetRelPath(int rnode, ForkNumber fn) {
    char* str = (char*)palloc(256);
    const char* const fnum = forkNames[fn];

    sprintf(str, "%d_%s", rnode, fnum);

    return str;
}