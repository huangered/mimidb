#include "catalog/storage.h"
#include "storage/smgr.h"

void RelationCreateStorage(Relation rel) {
    smgrcreate(rel, MAIN_FORKNUM);
}
