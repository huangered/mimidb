#ifndef _indexcmds_h_
#define _indexcmds_h_

#include "mimi.hpp"
#include "node/parsenode.hpp"

void DefineIndex(Oid relationId, CreateIndexStmt* stmt);

#endif // !_indexcmds_h_
