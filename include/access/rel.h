#ifndef _REL_H_
#define _REL_H_

#include "mimi.h"

typedef struct RelationData {
    Oid oid;
} RelationData;

typedef RelationData* Relation;

#endif