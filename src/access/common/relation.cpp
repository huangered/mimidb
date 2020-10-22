#include "access/relation.hpp"
#include "access/rel.hpp"

Relation 
relation_open(Oid relid) {
    Relation rel = RelationIdGetRelation(relid);

    return rel;
}

void 
relation_close(Relation rel) {
    RelationClose(rel);
}
