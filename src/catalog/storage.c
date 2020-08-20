#include "catalog/storage.h"
#include "access/relpath.h"
#include "access/rel.h"
#include "storage/fd.h"
#include "util/mctx.h"

void RelationCreateStorage(Relation rel) {
    char* path = GetRelPath(rel->rnode, MAIN_FORKNUMBER);
    file_init(path);
    pfree(path);
}
