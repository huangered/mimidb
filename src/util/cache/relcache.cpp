#include "access/genam.hpp"
#include "access/heaptuple.hpp"
#include "access/scankey.hpp"
#include "access/relcache.hpp"
#include "access/rel.hpp"
#include "access/relation.hpp"
#include "catalog/mimi_attribute.hpp"
#include "catalog/mimi_type.hpp"
#include "catalog/mimi_code.hpp"
#include "storage/smgr.hpp"
#include "util/builtins.hpp"
#include "util/hash.hpp"
#include "util/mctx.hpp"

Hash* relhash;

static void formrdesc(const char* relname, Oid reltype, int natts, const FormData_mimi_attribute* attrs);
static void relationCacheInsert(Relation rel);
static Relation relationCacheLookup(Oid relid);
static void RelationBuildTuple(Relation rel, TupleDesc tupleDesc);
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
        .att_name = "oid",
        .att_len = sizeof(int),
        .typid = 1
    },
        {
        .att_name = "relkind",
        .att_len = sizeof(int),
        .typid = 1
    },
        {
        .att_name = "relpages",
        .att_len = sizeof(int),
        .typid = 1
    },
        {
        .att_name = "tuples",
        .att_len = sizeof(int),
        .typid = 1
    }
};

static const FormData_mimi_attribute desc_pg_attribute[1] = {
    {
        .att_name = "oid",
        .att_len = sizeof(int),
        .typid = 1
    } 
};
static const FormData_mimi_attribute desc_pg_type[1] = {
    {
        .att_name = "oid",
        .att_len = sizeof(int),
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
    Relation rel = (Relation)palloc(sizeof(RelationData));

    /*
    init the ref count: 1 because it needs keep in cache
    */
    rel->refcount = 1;
    rel->oid = reltype;
    rel->rnode = reltype;
    rel->root_blkno = 0;
    rel->rd_rel = (Form_mimi_class)palloc(sizeof(FormData_mimi_class));
    strcpy(rel->rd_rel->relname, relname);

    rel->tb_am = table_route();
    // build relation tuple desc
    rel->tupleDesc = CreateTempTupleDesc(natts);
    for (int i = 0; i < natts; i++) {
        FormData_mimi_attribute* attr = (FormData_mimi_attribute * )(attrs + i);
        memcpy(&rel->tupleDesc->attr[i], attr, sizeof(FormData_mimi_attribute));

    }
    rel->rd_smgr = (SMgrRelationData*)palloc(sizeof(SMgrRelationData));
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

    Relation heaprel = (Relation)palloc(sizeof(RelationData));
    heaprel->oid = oid;
    heaprel->rd_rel = (Form_mimi_class)palloc(sizeof(FormData_mimi_class));
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
    Relation heaprel = (Relation)palloc(sizeof(RelationData));
    heaprel->oid = oid;
    heaprel->rnode = oid;
    heaprel->rd_rel = (Form_mimi_class)palloc(sizeof(FormData_mimi_class));
    strcpy(heaprel->rd_rel->relname, relname);

    RelationBuildTuple(heaprel, tupdesc);

    heaprel->refcount = 0;
    return heaprel;
}

void RelationBuildTuple(Relation heaprel, TupleDesc tupdesc) {
    // find tuple desc from meta data

    heaprel->tupleDesc = (TupleDesc)palloc(sizeof(TupleDescData));
    heaprel->tupleDesc->natts = tupdesc->natts;
    for (int i = 0; i < heaprel->tupleDesc->natts; i++) {
        heaprel->tupleDesc->attr[i].att_len = tupdesc->attr[i].att_len;
        heaprel->tupleDesc->attr[i].typid = tupdesc->attr[i].typid;
        strcpy(heaprel->tupleDesc->attr[i].att_name, tupdesc->attr[i].att_name);
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