#include "catalog/heap.h"
#include "access/rel.h"
#include "util/mctx.h"
#include "catalog/storage.h"
#include "catalog/mimi_code.h"

static void AddRelationPgClass(Relation pgclassdesc, Relation heaprel);

Relation heap_create(const char* name, Oid relid, TupleDesc tupDesc) {
    Relation pg_class_rel;
    Relation heap_rel;


    pg_class_rel = RelationIdGetRelation(ClassRelationId);
    // build relation
    heap_rel = BuildRelation(relid);

    // create tuple in mimi_class
    AddRelationPgClass(pg_class_rel, heap_rel);
    // create basic folder
    RelationCreateStorage(heap_rel);
    // create storage file

    return heap_rel;
}

void AddRelationPgClass(Relation pg_class_desc, Relation heap_rel) {

}