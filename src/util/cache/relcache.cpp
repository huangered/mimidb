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
#include "util/hashmap.hpp"

RelCache* cache = nullptr;

extern void RelationCacheInit() {
    cache = new RelCache;
}

Relation RelationIdGetRelation(Oid relid) {
    return cache->GetRelation(relid);
}
void RelationClose(Relation rel) {
    cache->CloseRelation(rel);
}

Relation BuildLocalRelation(Oid oid, const char* name, TupleDesc tupDesc) {
    return cache->BuildLocalRelation(oid, name, tupDesc);
}

Relation BuildRelationDesc(Oid oid, bool insert) {
    return cache->BuildRelationDesc(oid, insert);
}

// private area

static const FormData_mimi_attribute desc_pg_class[4] = {
    {
         1,
         {"oid"},
         sizeof(int),
         0,
         1
    },
    {
         1,
         {"relkind"},
         sizeof(int),
         0,
         1
    },
    {
         1,
         {"relpages"},
         sizeof(int),
         0,
         1
    },
    {
         1,
         {"tuples"},
         sizeof(int),
         0,
         1
    }
};

static const FormData_mimi_attribute desc_pg_attribute[1] = {
    {
         1,
         {"oid"},
         sizeof(int),
         0,
         1
    } 
};

static const FormData_mimi_attribute desc_pg_type[1] = {
    {
         1,
	     {"oid"},
	     sizeof(int),
         0,
         1
    }
};

/*
1. init the relation cache
2. insert the basic system relation
*/
RelCache::RelCache() {
    _formrdesc("mimi_class", ClassRelationId, 4, desc_pg_class);
    _formrdesc("mimi_attribute", AttributeRelationId, 1, desc_pg_attribute);
    _formrdesc("mimi_type", TypeRelationId, 1, desc_pg_type);
}

Relation
RelCache::GetRelation(Oid relid) {
    RelCacheEntry entry;

    if (_relhash.Get(relid, &entry)) {
        entry.rel->refcount += 1;
        return entry.rel;
    }

    Relation rel = BuildRelationDesc(relid, true);

    return rel;
}

void
RelCache::CloseRelation(Relation rel) {
    rel->refcount -= 1;
    if (rel->refcount == 0) {
        //remove from cache;
    }
}

/*
1. this method is for load system relation (mimi_class, mimi_attribute, etc)
2. insert the rel into relcache by hardcode
*/
void
RelCache::_formrdesc(const char* relname, Oid reltype, int natts, const FormData_mimi_attribute* attrs) {
    Relation rel = new RelationData;

    /*
    init the ref count: 1 because it needs keep in cache
    */
    rel->refcount = 1;
    rel->rd_id = reltype;
    rel->rd_rel = new FormData_mimi_class;
    strcpy(rel->rd_rel->relname, relname);

    rel->tb_am = nullptr;// table_route();
    // build relation tuple desc
    rel->tupleDesc = CreateTempTupleDesc(natts);
    for (int i = 0; i < natts; i++) {
        FormData_mimi_attribute* attr = (FormData_mimi_attribute*)(attrs + i);
        memcpy(&rel->tupleDesc->attr[i], attr, sizeof(FormData_mimi_attribute));

    }
    rel->rd_smgr = nullptr;

    RelCacheEntry entry{ rel->rd_id, rel };
    _relhash.Put(rel->rd_id, entry);
}

/*
1. find a relation from raw data
2. if insert == true, insert into cache
*/
Relation
RelCache::BuildRelationDesc(Oid oid, bool insert) {
    HeapTuple heap_tup;
    Form_mimi_class rel_class;

    heap_tup = _scanMimiRelation(oid);
    rel_class = (Form_mimi_class)(heap_tup->t_data);

    Relation heaprel = new RelationData;
    heaprel->rd_id = oid;
    heaprel->rd_rel = new FormData_mimi_class;
    strcpy(heaprel->rd_rel->relname, rel_class->relname);

    //RelationBuildTuple(heaprel);

    heaprel->refcount = 0;
    if (insert) {
        RelCacheEntry entry{ heaprel->rd_id, heaprel };
        _relhash.Put(heaprel->rd_id, entry);
    }
    return heaprel;
}


/*
1. build a relcache entry
2. return relation object
*/
Relation
RelCache::BuildLocalRelation(Oid oid, const char* relname, TupleDesc tupdesc) {
    Relation heaprel = new RelationData;
    heaprel->rd_id = oid;
    heaprel->rd_rel = new FormData_mimi_class;
    strcpy(heaprel->rd_rel->relname, relname);

    _relationBuildTuple(heaprel, tupdesc);

    heaprel->refcount = 0;
    return heaprel;
}

void
RelCache::_relationBuildTuple(Relation heaprel, TupleDesc tupdesc) {
    // find tuple desc from meta data

    heaprel->tupleDesc = new TupleDescData;
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
HeapTuple
RelCache::_scanMimiRelation(Oid relid) {
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
