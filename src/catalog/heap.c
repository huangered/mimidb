#include "access/heap.h"
#include "catalog/heap.h"
#include "access/rel.h"
#include "common/relation.h"
#include "util/mctx.h"
#include "catalog/storage.h"
#include "catalog/mimi_code.h"
#include "access/heaptuple.h"

static Relation heap_create(Oid relid, const char* name, TupleDesc tupdesc);
static void AddRelationPgClass(Relation mimiclassdesc, Relation heaprel);
static void InsertMimiClassTuple(Relation mimiclassdesc, Form_mimi_class heaprel);

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

    relation_close(pg_class_rel);
    relation_close(heap_rel);

    return heap_rel;
}

Relation
heap_create(Oid relid, const char* name, TupleDesc tupdesc) {
    Relation heap_rel = BuildLocalRelation(relid, name, tupdesc);

    // create storage file
    RelationCreateStorage(heap_rel);

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

    HeapTuple tuple = heap_form_tuple(mimi_class_desc->tupleDesc, values);

    simple_heap_insert(mimi_class_desc, tuple);

    pfree(tuple);
}