#include "access/genam.h"
#include "access/heaptuple.h"
#include "access/scankey.h"
#include "access/relcache.h"
#include "access/rel.h"
#include "access/relation.h"
#include "catalog/mimi_attribute.h"
#include "catalog/mimi_type.h"
#include "catalog/mimi_code.h"
#include "storage/smgr.h"
#include "util/builtins.h"
#include "util/hash.h"
#include "util/mctx.h"

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
    RelCacheEntry* entry = (RelCacheEntry*)hash_search(relhash, Add, &rel->oid);
    entry->oid = rel->oid;
    entry->rel = rel;
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

static const FormData_mimi_attribute desc_pg_class[4] = {
    {
        .attname = "oid",
        .attlen = sizeof(int),
        .typid = 1
    },
        {
        .attname = "relkind",
        .attlen = sizeof(int),
        .typid = 1
    },
        {
        .attname = "relpages",
        .attlen = sizeof(int),
        .typid = 1
    },
        {
        .attname = "tuples",
        .attlen = sizeof(int),
        .typid = 1
    }
};

static const FormData_mimi_attribute desc_pg_attribute[1] = {
    {
        .attname = "oid",
        .attlen = sizeof(int),
        .typid = 1
    } 
};
static const FormData_mimi_attribute desc_pg_type[1] = {
    {
        .attname = "oid",
        .attlen = sizeof(int),
    }
};

/*
1. init the relation cache
2. insert the basic system relation
*/
void RelationCacheInit() {
    relhash = hash_create("rel_cache_hash", OidHashValue, OidHashEqual, sizeof(Oid), sizeof(struct RelCacheEntry));

    formrdesc("mimi_class", ClassRelationId, 4, desc_pg_class);
    formrdesc("mimi_attribute", AttributeRelationId, 1, desc_pg_attribute);
    formrdesc("mimi_type", TypeRelationId, 1, desc_pg_type);
}

Relation RelationIdGetRelation(Oid relid) {
    Relation rel = relationCacheLookup(relid);

    if (rel != NULL) {
        rel->refcount += 1;
        return rel;
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
    rel->oid = reltype;
    rel->rnode = reltype;
    rel->root_blkno = 0;
    rel->rd_rel = palloc(sizeof(FormData_mimi_class));
    strcpy(rel->rd_rel->relname, relname);

    rel->tb_am = table_route();
    // build relation tuple desc
    rel->tupleDesc = CreateTempTupleDesc(natts);
    for (int i = 0; i < natts; i++) {
        FormData_mimi_attribute* attr = attrs + i;
        memcpy(&rel->tupleDesc->attr[i], attr, sizeof(FormData_mimi_attribute));

    }
    rel->rd_smgr = palloc(sizeof(SMgrRelationData));
    rel->rd_smgr->smgr_fsm_nblocks = 0;
    relationCacheInsert(rel);
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
    strcpy(heaprel->rd_rel->relname, rel_class->relname);

    //RelationBuildTuple(heaprel);

    heaprel->refcount = 0;
    if (insert) {
        relationCacheInsert(heaprel);
    }
    return heaprel;
}


/*
1. build a relcache entry
2. return relation object
*/
Relation BuildLocalRelation(Oid oid, const char* relname, TupleDesc tupdesc) {
    Relation heaprel = palloc(sizeof(RelationData));
    heaprel->oid = oid;
    heaprel->rnode = oid;
    heaprel->rd_rel = palloc(sizeof(FormData_mimi_class));
    strcpy(heaprel->rd_rel->relname, relname);

    heaprel->tupleDesc = palloc(sizeof(TupleDescData));
    heaprel->tupleDesc->natts = tupdesc->natts;
    for (int i = 0; i < heaprel->tupleDesc->natts; i++) {
        heaprel->tupleDesc->attr[i].attlen = tupdesc->attr[i].attlen;
        heaprel->tupleDesc->attr[i].typid = tupdesc->attr[i].typid;
        strcpy(heaprel->tupleDesc->attr[i].attname, tupdesc->attr[i].attname);
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
        heaprel->tupleDesc->attr[i].attlen = tupdesc->attr[i].attlen;
        heaprel->tupleDesc->attr[i].typid = tupdesc->attr[i].typid;
        strcpy(heaprel->tupleDesc->attr[i].attname, tupdesc->attr[i].attname);
    }
}



/*
 * 扫描 mm_class 表，获取 relation tuple 信息
 */
HeapTuple ScanMimiRelation(Oid relid) {
    HeapTuple tup = NULL;
    ScanKeyData key[1];
    Relation pg_class_relation;
    SystemTableScan scan;

    ScanKeyInit(key, MIMI_CLASS_OID_LOCATION, BTEqualStrategyNumber, relid, OIDEQ_OID);
    pg_class_relation = relation_open(ClassRelationId);

    scan = systable_beginscan(pg_class_relation, 1, key);
    tup = systable_getnext(scan);
    systable_endscan(scan);

    relation_close(pg_class_relation);

    return tup;
}