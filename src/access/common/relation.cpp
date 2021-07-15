#include "access/relation.hpp"
#include "access/rel.hpp"
#include "access/relcache.hpp"

Relation
relation_open(Oid relid) {
    Relation rel = relcache->RelationIdGetRelation(relid);

    return rel;
}

void
relation_close(Relation rel) {
    relcache->RelationClose(rel);
}
