#include "access/relpath.hpp"

const char* const forkNames[] = {
    "main",						/* MAIN_FORKNUM */
    "fsm",						/* FSM_FORKNUM */
};

std::filesystem::path GetRelPath2(Oid dbNode, Oid relNode, ForkNumber fn) {
    char* str = new char[64];
    const char* const fnum = forkNames[fn];

    sprintf(str, "%lld_%lld_%s", dbNode, relNode, fnum);

    std::filesystem::path path{str};

    delete[] str;
    
    return path;
}