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
#include "access/sysattr.hpp"
#include "util/mctx.hpp"

RelCache* relcache = new RelCache{};

/*
* 硬编码的tuple描述信息
*/
static const FormData_mimi_attribute Desc_pg_class[4] = {
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
static const FormData_mimi_attribute Desc_pg_attribute[1] = {
    {
         1,
         {"oid"},
         sizeof(int),
         0,
         1
    } 
};
static const FormData_mimi_attribute Desc_pg_type[1] = {
    {1,"oid", sizeof(int), 1 },

};

/*
1. init the relation cache
2. insert the basic system relation
*/
RelCache::RelCache() {
    _formrdesc("mimi_class", ClassRelationId, 4, Desc_pg_class);
    _formrdesc("mimi_attribute", AttributeRelationId, 1, Desc_pg_attribute);
    _formrdesc("mimi_type", TypeRelationId, 1, Desc_pg_type);
}

Relation
RelCache::RelationIdGetRelation(Oid relid) {
    RelCacheEntry entry;
    // 查找cache
    if (cache.Get(relid, &entry)) {
        entry.rel->IncRefCnt();
        return entry.rel;
    }
    // 从数据库中加载 relation
    Relation rel = BuildRelationDesc(relid, true);
    rel->IncRefCnt();
    return rel;
}

void
RelCache::RelationClose(Relation rel) {
    rel->DecRefCnt();
    if (rel->refcount == 0) {
        //remove from cache;
        cache.Remove(rel->rd_id);
    }
}

/*
1. this method is for load system relation (mimi_class, mimi_attribute, etc)
2. insert the rel into relcache by hardcode
*/
void
RelCache::_formrdesc(const char* relname, Oid reltype, int natts, const FormData_mimi_attribute* attrs) {
    Relation rel = new RelationData{};

    /*
    init the ref count: 1 because it needs keep in cache
    */
    rel->refcount = 1;
    rel->rd_id = reltype;
    rel->rd_rel = new FormData_mimi_class{};
    strcpy(rel->rd_rel->relname, relname);

    rel->tb_am = nullptr;// table_route();
    // build relation tuple desc
    rel->rd_tupledesc = CreateTempTupleDesc(natts);
    for (int i{ 0 }; i < natts; i++) {
        FormData_mimi_attribute* attr = (FormData_mimi_attribute*)(attrs + i);
        memcpy(rel->rd_tupledesc->GetNatt(i), attr, sizeof(FormData_mimi_attribute));

    }
    rel->rd_smgr = nullptr;

    RelCacheEntry entry{ rel->rd_id, rel };
    cache.Put(rel->rd_id, entry);
}

/*
1. find a relation from raw data
2. if insert == true, insert into cache
*/
Relation
RelCache::BuildRelationDesc(Oid targetRelId, bool insert) {
    Relation        relation;
    HeapTuple       mimi_class_tuple;
    Form_mimi_class relp;

    // 扫描 mimi_class 表，获取meta数据
    mimi_class_tuple = _ScanMimiRelation(targetRelId);

    // 没找到，返回空
    if (mimi_class_tuple == nullptr) {
        return nullptr;
    }

    relp = (Form_mimi_class)GETSTRUCT(mimi_class_tuple);

    relation = _AllocateRelationDesc(relp);

    //更新attrs
    _RelationBuildTupleDesc(relation);
    // 更新物理地址
    _RelationInitPhysicalAddr(relation);
    relation->refcount = 0;

    // 释放 heap_tup

    if (insert) {
        RelCacheEntry entry{ relation->rd_id, relation };
        cache.Put(relation->rd_id, entry);
    }
    return relation;
}


/*
1. build a relcache entry
2. return relation object
*/
Relation
RelCache::BuildLocalRelation(Oid oid, const char* relname, TupleDesc tupdesc) {
    Relation heaprel = new RelationData{};
    heaprel->rd_id = oid;
    heaprel->rd_rel = new FormData_mimi_class{};
    strcpy(heaprel->rd_rel->relname, relname);

    _RelationBuildTupleDesc(heaprel);

    heaprel->refcount = 0;
    return heaprel;
}

Relation
RelCache::_AllocateRelationDesc(Form_mimi_class relp) {
    Relation rel = new RelationData();
    rel->rd_smgr = nullptr;
    rel->rd_id = relp->oid;
    rel->rd_rel = new FormData_mimi_class();
    memcpy(rel->rd_rel, relp, sizeof(FormData_mimi_class));

    rel->rd_tupledesc = CreateTempTupleDesc(relp->relnatts);

    return rel;
}

// 填充 attr
void
RelCache::_RelationBuildTupleDesc(Relation rel) {
    HeapTuple        pg_attr_tuple;
    Relation         pg_attr_relation;
    SysTableScanDesc pg_attr_scan;
    ScanKeyData      key[1] = { {ObjectIdAttributeNumber, BTEqualStrategyNumber, rel->rd_id, OIDCMP_OID} };
    // search attribute table by rel->oid

    pg_attr_relation = relation_open(AttributeRelationId);
    pg_attr_scan = systable_beginscan(pg_attr_relation, 1, key);

    // 填充rel->tupleDesc
    while ((pg_attr_tuple = systable_getnext(pg_attr_scan))) {
        Form_mimi_attribute attp;
        int att_num;

        attp = (Form_mimi_attribute)GETSTRUCT(pg_attr_tuple);
        att_num = attp->att_order;
        memcpy(rel->rd_tupledesc->GetNatt(att_num), attp, sizeof(FormData_mimi_attribute));
    }

    systable_endscan(pg_attr_scan);

    relation_close(pg_attr_relation);
}

void
RelCache::_RelationInitPhysicalAddr(Relation rel) {
    // 扫描class 表，查找relfilenode
}

/*
 * 扫描 mm_class 表，获取 relation tuple 信息
 */
HeapTuple
RelCache::_ScanMimiRelation(Oid relid) {
    HeapTuple        pg_class_tuple;
    Relation         pg_class_relation;
    SysTableScanDesc pg_class_scan;
    ScanKeyData      key[1] = { { ObjectIdAttributeNumber, BTEqualStrategyNumber, relid, OIDCMP_OID} };

    pg_class_relation = relation_open(ClassRelationId);

    pg_class_scan = systable_beginscan(pg_class_relation, 1, key);
    pg_class_tuple = systable_getnext(pg_class_scan);
    // 查找成功，复制一个新 heap tuple
    if (pg_class_tuple != nullptr) {
        pg_class_tuple = heap_copytuple(pg_class_tuple);
    }

    systable_endscan(pg_class_scan);

    relation_close(pg_class_relation);

    return pg_class_tuple;
}