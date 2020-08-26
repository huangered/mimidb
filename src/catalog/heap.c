#include "access/heap.h"
#include "catalog/heap.h"
#include "access/rel.h"
#include "common/relation.h"
#include "util/mctx.h"
#include "catalog/storage.h"
#include "catalog/mimi_code.h"

static void AddRelationPgClass(Relation mimiclassdesc, Relation heaprel);
static void InsertMimiClassTuple(Relation mimiclassdesc, Form_mimi_class heaprel);

Relation heap_create(const char* name, Oid relid, TupleDesc tupDesc) {
    Relation pg_class_rel;
    Relation heap_rel;


    pg_class_rel = relation_open(ClassRelationId);
    // build relation
    heap_rel = BuildLocalRelation(relid, name, tupDesc);

    // create storage file
    RelationCreateStorage(heap_rel);

    // create tuple in mimi_class
    AddRelationPgClass(pg_class_rel, heap_rel);

    relation_close(pg_class_rel);
    relation_close(heap_rel);

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
    HeapTuple tuple = palloc(sizeof(HeapTupleData));
    tuple->t_len = 100;

    simple_heap_insert(mimi_class_desc, tuple);
}