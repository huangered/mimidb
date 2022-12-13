#ifndef _indexcmds_h_
#define _indexcmds_h_

#include "mimi.h"
#include "node/parsenode.h"

void DefineIndex(Oid relationId, struct CreateIndexStmt* stmt);

#endif // !_indexcmds_h_
