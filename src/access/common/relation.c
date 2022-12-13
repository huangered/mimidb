#include "access/relation.h"
#include "access/rel.h"
#include "access/relcache.h"

Relation
relation_open(Oid relid) {
    //todo
    //Relation rel = relcache->RelationIdGetRelation(relid);

    //return rel;
    return NULL;
}

void
relation_close(Relation rel) {
    //relcache->RelationClose(rel);
}
