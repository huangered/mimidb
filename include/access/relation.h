#ifndef _relation_hpp_
#define _relation_hpp_

#include "mimi.h"

typedef struct RelationData* Relation;

Relation relation_open(Oid relid);
void relation_close(Relation rel);

#endif // !_relation_h_
