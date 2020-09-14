#include "commands/create.h"
#include "catalog/heap.h"
#include "catalog/index.h"
#include "commands/indexcmds.h"

void DefineRelation(CreateStmt* stmt) {
	const char* name;
	Oid id;
	TupleDesc tupdesc;
	heap_create(name, id, tupdesc);

	DefineIndex(id, NULL);
}