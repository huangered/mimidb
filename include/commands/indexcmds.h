#ifndef _indexcmds_h_
#define _indexcmds_h_

#include "mimi.h"

typedef struct IndexStmt {
    int i;
} IndexStmt;

void DefineIndex(Oid relationId, IndexStmt* stmt);

#endif // !_indexcmds_h_
