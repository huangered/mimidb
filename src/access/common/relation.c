#include "common/relation.h"
#include "access/rel.h"

Relation 
relation_open(Oid relid) {
    Relation rel = RelationIdGetRelation(relid);

    return rel;
}

void 
relation_close(Relation rel) {
    RelationClose(rel);
}
