#include "commands/indexcmds.h"
#include "catalog/index.h"

void DefineIndex(Oid relationId, CreateIndexStmt* stmt) {
	index_create(NULL, relationId, InvalidOid, NULL);
}