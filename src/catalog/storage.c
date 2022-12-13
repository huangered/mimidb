#include "catalog/storage.h"
#include "storage/smgr.h"
#include "access/rel.h"

void
RelationCreateStorage(Relation rel) {
    // todo:
    // smgr->Create(rel->rd_smgr, MAIN_FORKNUM);
}

void
RelationDropStorage(Relation rel) {
}
