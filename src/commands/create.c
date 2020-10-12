#include "commands/create.h"
#include "catalog/heap.h"
#include "catalog/index.h"
#include "commands/indexcmds.h"

static TupleDesc formTupleDesc(List* columns);

void DefineRelation(CreateTableStmt* stmt) {
	const char* name = stmt->relname;
	Oid id = 1;
	TupleDesc tupdesc = (TupleDesc)formTupleDesc(stmt->columns);
	heap_create_with_catalog(name, id, tupdesc);

	DefineIndex(id, NULL);
}

TupleDesc
formTupleDesc(List* columns) {
	return NULL;
}