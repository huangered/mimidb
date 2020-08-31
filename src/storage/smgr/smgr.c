#include "storage/smgr.h"
#include "access/rel.h"
#include "access/relpath.h"
#include "util/mctx.h"
#include <Windows.h>
#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")

bool smgrexists(Relation rel, ForkNumber number) {
    bool result = false;
    char* path = GetRelPath(rel->rnode, number);

    result = PathFileExists(path);

    pfree(path);
    return result;
}

BlockNumber smgrblocks(Relation rel, ForkNumber number) {
    return 0;
}