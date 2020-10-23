#include "catalog/storage.h"
#include "storage/smgr.h"
#include "access/rel.h"

void RelationCreateStorage(Relation rel) {
    smgrcreate(rel->rnode, MAIN_FORKNUM);
}

void
RelationDropStorage(Relation rel) {

}
