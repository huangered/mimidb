#include "access/relcache.h"
#include "access/rel.h"
#include "util/hash.h"
#include "catalog/mimi_attribute.h"
#include "catalog/mimi_code.h"
#include "util/mctx.h"

Hash* relhash;

static void formrdesc(const char* relname, Oid reltype, int natts, const FormData_mimi_attribute* attrs);

void RelationCacheInit();

typedef struct RelCacheEntry {
    Oid oid;
    Relation rel;
} RelCacheEntry;

/*
1. init the relation cache
2. insert the basic system relation
*/
void RelationCacheInit() {
    relhash = hash_create("rel_cache_hash", NULL, NULL, sizeof(Oid), sizeof(struct RelCacheEntry));

    formrdesc("mimi_class", ClassRelationId, 20, NULL);
    formrdesc("mimi_attribute", AttributeRelationId, 20, NULL);
}

Relation RelationIdGetRelation(Oid relid) {
    RelCacheEntry* entry = (RelCacheEntry*)hash_search(relhash, Search, &relid);
    if (entry) {
        return entry->rel;
    }
    else {
        return NULL;
    }
}

void RelationClose(Relation rel) {
    rel->refcount -= 1;
    if (rel->refcount == 0) {
        //remove from cache;
    }
}

/*
1. this method is for load system relation (mimi_class, mimi_attribute, etc)
2. insert the rel into relcache by hardcode
*/
void formrdesc(const char* relname, Oid reltype, int natts, const FormData_mimi_attribute* attrs) {
    Relation rel = palloc(sizeof(RelationData));

    /*
    init the ref count: 1 because it needs keep in cache
    */
    rel->refcount = 1;

    rel->rd_rel = palloc(sizeof(FormData_mimi_class));
    strcpy(rel->rd_rel->name, relname);

    rel->tb_am = table_route();

}

Relation BuildRelation(Oid oid, const char* relname, TupleDesc tupdesc) {
    Relation heaprel = palloc(sizeof(RelationData));
    heaprel->oid = oid;
    heaprel->rd_rel = palloc(sizeof(FormData_mimi_class));
    strcpy(heaprel->rd_rel->name, relname);

    heaprel->tupleDesc = palloc(sizeof(TupleDescData));
    heaprel->tupleDesc->natts = tupdesc->natts;
    for (int i = 0; i < heaprel->tupleDesc->natts; i++) {
        heaprel->tupleDesc->attr[i].oid = tupdesc->attr[i].oid;
        heaprel->tupleDesc->attr[i].length = tupdesc->attr[i].length;
        heaprel->tupleDesc->attr[i].type = tupdesc->attr[i].type;
        memcpy(heaprel->tupleDesc->attr[i].name, tupdesc->attr[i].name, 64);
    }
    return heaprel;
}