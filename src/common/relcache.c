#include "access/relcache.h"
#include "access/rel.h"
#include "common/relation.h"
#include "util/hash.h"
#include "catalog/mimi_attribute.h"
#include "catalog/mimi_code.h"
#include "util/mctx.h"
#include "access/heaptuple.h"

Hash* relhash;

static void formrdesc(const char* relname, Oid reltype, int natts, const FormData_mimi_attribute* attrs);
static void relationCacheInsert(Relation rel);
static Relation relationCacheLookup(Oid relid);
static void RelationBuildTuple(Relation rel);
static HeapTuple ScanMimiRelation(Oid relid);

typedef struct RelCacheEntry {
    Oid oid;
    Relation rel;
} RelCacheEntry;

static uint32 OidHashValue(const void* key, Size keysize) {
    return *((Oid*)key);
}

static bool OidHashEqual(const void* left, const void* right, Size keysize) {
    Oid* l = (Oid*)left;
    Oid* r = (Oid*)right;
    return *r == *l;
}

static void relationCacheInsert(Relation rel) {

}

static Relation relationCacheLookup(Oid relid) {
    RelCacheEntry* entry = (RelCacheEntry*)hash_search(relhash, Search, &relid);
    if (entry) {
        return entry->rel;
    }
    else {
        return NULL;
    }
}


/*
1. init the relation cache
2. insert the basic system relation
*/
void RelationCacheInit() {
    relhash = hash_create("rel_cache_hash", OidHashValue, OidHashEqual, sizeof(Oid), sizeof(struct RelCacheEntry));

    formrdesc("mimi_class", ClassRelationId, 20, NULL);
    formrdesc("mimi_attribute", AttributeRelationId, 20, NULL);
}

Relation RelationIdGetRelation(Oid relid) {
    Relation rel = relationCacheLookup(relid);

    if (rel != NULL) {
        rel->refcount += 1;
    }

    rel = BuildRelationDesc(relid, true);

    return rel;
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

/*
1. find a relation from raw data
2. if insert == true, insert into cache
*/
Relation BuildRelationDesc(Oid oid, bool insert) {
    HeapTuple heap_tup;
    Form_mimi_class rel_class;

    heap_tup = ScanMimiRelation(oid);
    rel_class = (Form_mimi_class)(heap_tup->t_data);

    Relation heaprel = palloc(sizeof(RelationData));
    heaprel->oid = oid;
    heaprel->rd_rel = palloc(sizeof(FormData_mimi_class));
    strcpy(heaprel->rd_rel->name, rel_class->name);

    RelationBuildTuple(heaprel);

    heaprel->refcount = 0;
    if (insert) {
        relationCacheInsert(heaprel);
    }
    return heaprel;
}

// ======== private methods ==========

Relation BuildLocalRelation(Oid oid, const char* relname, TupleDesc tupdesc) {
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
        strcpy(heaprel->tupleDesc->attr[i].name, tupdesc->attr[i].name);
    }

    heaprel->refcount = 0;
    return heaprel;
}

void RelationBuildTuple(Relation heaprel) {
    // find tuple desc from meta data
    TupleDesc tupdesc;

    heaprel->tupleDesc = palloc(sizeof(TupleDescData));
    heaprel->tupleDesc->natts = tupdesc->natts;
    for (int i = 0; i < heaprel->tupleDesc->natts; i++) {
        heaprel->tupleDesc->attr[i].oid = tupdesc->attr[i].oid;
        heaprel->tupleDesc->attr[i].length = tupdesc->attr[i].length;
        heaprel->tupleDesc->attr[i].type = tupdesc->attr[i].type;
        strcpy(heaprel->tupleDesc->attr[i].name, tupdesc->attr[i].name);
    }
}

HeapTuple ScanMimiRelation(Oid relid) {
    return NULL;
}