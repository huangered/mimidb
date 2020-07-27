#ifndef _REL_H_
#define _REL_H_

#include "mimi.h"

typedef struct RelationData {
    Oid oid;
} RelationData;

typedef RelationData* Relation;

typedef enum ForkNumber {
    MAIN_FORKNUMBER = 0,
    FSM_FORKNUM,
} ForkNumber;

#endif