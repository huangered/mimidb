#include "access/rel.h"
#include "util/mctx.h"

const char* const forkNames[] = {
    "main",						/* MAIN_FORKNUM */
    "fsm",						/* FSM_FORKNUM */
};

char* GetRelPath(int rnode, ForkNumber fn) {
    char* str = palloc(256);
    char* fnum = forkNames[fn];

    sprintf(str, "data/%d_%s", rnode, fnum);

    return str;
}