#include "access/heap.hpp"
#include "catalog/heap.hpp"
#include "access/rel.hpp"
#include "access/relation.hpp"
#include "util/mctx.hpp"
#include "catalog/storage.hpp"
#include "catalog/mimi_code.hpp"
#include "access/heaptuple.hpp"
#include "catalog/mimi_attribute.hpp"

static Relation heap_create(Oid relid, const char* name, TupleDesc tupdesc);
static void AddRelationPgClass(Relation mimiclassdesc, Relation heaprel);
static void AddRelationMimiAttribute(Oid relId, TupleDesc rd_tupledesc);
static void InsertMimiClassTuple(Relation mimiclassdesc, Form_mimi_class heaprel);
static void InsertMimiAttributeTuple(Relation mimi_attribute_rel, Form_mimi_attribute new_attribute);
/*
Create a heap relation
1. build relation local
2. create storage folder
3. add relation tup into mimi_class table
4. close the relation
*/
Relation 
heap_create_with_catalog(const char* name, Oid relid, TupleDesc tupDesc) {
    Relation pg_class_rel;
    Relation heap_rel;

    pg_class_rel = relation_open(ClassRelationId);
    // build relation
    heap_rel = heap_create(relid, name, tupDesc);

    // create tuple in mimi_class
    AddRelationPgClass(pg_class_rel, heap_rel);
    // create tuple in mimi_attribute
    AddRelationMimiAttribute(heap_rel->rd_id, tupDesc);
    relation_close(pg_class_rel);
    relation_close(heap_rel);

    return heap_rel;
}

Relation
heap_create(Oid relid, const char* name, TupleDesc tupdesc) {
    Relation heap_rel = relcache->BuildLocalRelation(relid, name, tupdesc);

    switch (heap_rel->rd_rel->relkind) {
    case RELKIND_INDEX:
    case RELKIND_RELATION:
        // create storage file
        RelationCreateStorage(heap_rel);
        break;
    }
    return heap_rel;
}

void AddRelationPgClass(Relation mimi_class_desc, Relation heap_rel) {
    Form_mimi_class new_rel_reltup;

    new_rel_reltup = heap_rel->rd_rel;

    new_rel_reltup->relpages = 0;
    new_rel_reltup->tuples = 0;

    /* now build and insert the tuple */
    InsertMimiClassTuple(mimi_class_desc, new_rel_reltup);
}

void
InsertMimiClassTuple(Relation mimi_class_desc, Form_mimi_class new_rel_reltup) {
    Datum values[4];
    values[0] = IntGetDatum(new_rel_reltup->oid);
    values[1] = IntGetDatum(new_rel_reltup->relkind);
    values[2] = IntGetDatum(new_rel_reltup->relpages);
    values[3] = IntGetDatum(new_rel_reltup->tuples);

    HeapTuple tuple = heap_form_tuple(mimi_class_desc->rd_tupledesc, values);

    mimi_class_desc->tb_am->simple_heap_insert(mimi_class_desc, tuple);

    std::free(tuple);
}

void
AddRelationMimiAttribute(Oid relId, TupleDesc rd_tupledesc) {
    Relation rel = relation_open(AttributeRelationId);

    for (int i = 0; i < rd_tupledesc->GetNatts(); i++) {
        Form_mimi_attribute attr = rd_tupledesc->GetNatt(i);
        attr->att_relid = relId;
        InsertMimiAttributeTuple(rel, attr);
    }

    relation_close(rel);
}

/*
构造和插入mimi attribute tuple
*/
void
InsertMimiAttributeTuple(Relation mimi_attribute_rel, Form_mimi_attribute new_attribute) {
    Datum values[5];
    values[0] = IntGetDatum(new_attribute->att_relid);
    values[1] = IntGetDatum(new_attribute->att_len);
    values[2] = PointerGetDatum(new_attribute->att_name);
    values[3] = IntGetDatum(new_attribute->typ_id);

    HeapTuple tuple = heap_form_tuple(mimi_attribute_rel->rd_tupledesc, values);

    mimi_attribute_rel->tb_am->simple_heap_insert(mimi_attribute_rel, tuple);

    std::free(tuple);
}