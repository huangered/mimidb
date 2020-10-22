#include "catalog/storage.hpp"
#include "storage/smgr.hpp"

void RelationCreateStorage(Relation rel) {
    smgrcreate(rel, MAIN_FORKNUM);
}

void
RelationDropStorage(Relation rel) {

}
