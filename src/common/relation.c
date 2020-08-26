#include "common/relation.h"
#include "access/rel.h"

Relation relation_open(Oid relid) {
    return NULL;
}

void relation_close(Relation rel) {
    rel->refcount -= 1;
    if (rel->refcount == 0) {
        // remove from cache.
    }
}
