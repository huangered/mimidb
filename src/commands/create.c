#include "commands/create.h"
#include "catalog/heap.h"
#include "catalog/index.h"
#include "commands/indexcmds.h"

void DefineRelation(CreateStmt* stmt) {
	const char* name;
	Oid id;
	TupleDesc tupdesc;
	heap_create_with_catalog(name, id, tupdesc);

	DefineIndex(id, NULL);
}