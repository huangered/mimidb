#include "commands/indexcmds.h"
#include "catalog/index.h"

void DefineIndex(Oid relationId, IndexStmt* stmt) {
	index_create(NULL, relationId, InvalidOid, NULL);
}