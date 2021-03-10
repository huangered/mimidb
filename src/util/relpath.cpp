#include "access/relpath.hpp"

const char* const forkNames[] = {
    "main",						/* MAIN_FORKNUM */
    "fsm",						/* FSM_FORKNUM */
};

char* GetRelPath(int rnode, ForkNumber fn) {
    char* str = new char[64];
    const char* const fnum = forkNames[fn];

    sprintf(str, "%d_%s", rnode, fnum);

    return str;
}

std::filesystem::path GetRelPath2(Oid rnode, ForkNumber fn) {
    char* str = new char[64];
    const char* const fnum = forkNames[fn];

    sprintf(str, "%lld_%s", rnode, fnum);

    std::filesystem::path path{str};

    delete[] str;
    
    return path;
}