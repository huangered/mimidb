#include "access/relcache.h"
#include "access/rel.h"
#include "util/hash.h"

Hash* relhash;

void RelationCacheInit();

struct RelEntry {
    Oid oid;
    Relation rel;
};

void RelationCacheInit() {
    relhash = hash_create("rel_cache_hash", NULL, NULL, sizeof(Oid), sizeof(struct RelEntry));
}

Relation RelationIdGetRelation(Oid relid) {
    return NULL;
}

void RelationClose(Relation rel) {

}


Relation BuildRelation(Oid oid, const char* name, TupleDesc tupdesc) {
    Relation heaprel = palloc(sizeof(RelationData));
    heaprel->oid = oid;
    heaprel->name = palloc(strlen(name));
    memset(heaprel->name, 0, strlen(name));
    strcpy(heaprel->name, name);
    heaprel->tupleDesc = palloc(sizeof(TupleDescData));
    heaprel->tupleDesc->natts = tupdesc->natts;
    for (int i = 0; i < heaprel->tupleDesc->natts; i++) {
        heaprel->tupleDesc->attr[i].oid = tupdesc->attr[i].oid;
        heaprel->tupleDesc->attr[i].length = tupdesc->attr[i].length;
        heaprel->tupleDesc->attr[i].type = tupdesc->attr[i].type;
        memcpy(heaprel->tupleDesc->attr[i].name, tupdesc->attr[i].name, 64);
    }

}