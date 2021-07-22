#include "access/relpath.hpp"

const char* const forkNames[] = {
    "main", /* MAIN_FORKNUM */
    "fsm",  /* FSM_FORKNUM */
};

char*
GetRelPath(Oid dbNode, Oid relNode, ForkNumber fn) {
    char* str              = new char[64];
    const char* const fnum = forkNames[fn];

    sprintf(str, "%lld_%lld_%s", dbNode, relNode, fnum);

    return str;
}