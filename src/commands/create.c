#include "commands/create.h"
#include "catalog/heap.h"
#include "catalog/index.h"
#include "commands/indexcmds.h"

static TupleDesc formTupleDesc(char* columns);

void DefineRelation(CreateStmt* stmt) {
	const char* name = stmt->relname;
	Oid id = 1;
	TupleDesc tupdesc = formTupleDesc(stmt->column);
	heap_create_with_catalog(name, id, tupdesc);

	DefineIndex(id, NULL);
}

TupleDesc
formTupleDesc(char* columns) {
	return NULL;
}