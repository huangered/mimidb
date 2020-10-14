#include "util/mctx.h"
#include "access/relpath.h"

const char* const forkNames[] = {
    "main",						/* MAIN_FORKNUM */
    "fsm",						/* FSM_FORKNUM */
};

char* GetRelPath(int rnode, ForkNumber fn) {
    char* str = palloc(256);
    char* fnum = forkNames[fn];

    sprintf(str, "%d_%s", rnode, fnum);

    return str;
}