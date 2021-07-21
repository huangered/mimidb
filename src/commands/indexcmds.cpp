#include "commands/indexcmds.hpp"
#include "catalog/index.hpp"

void
DefineIndex(Oid relationId, CreateIndexStmt* stmt) {
    index_create(NULL, relationId, InvalidOid, NULL);
}