#include "catalog/storage.hpp"
#include "storage/smgr.hpp"
#include "access/rel.hpp"

void RelationCreateStorage(Relation rel) {
    smgr->Create(rel->rd_smgr, MAIN_FORKNUM);
}

void
RelationDropStorage(Relation rel) {
    smgr->Remove(rel->rd_smgr);
}
