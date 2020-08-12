#ifndef _REL_H_
#define _REL_H_

#include "mimi.h"
#include "storage/block.h"

typedef struct RelationData {
    Oid oid;
    int rnode;
    BlockNum root_blkno;
} RelationData;

typedef RelationData* Relation;

typedef enum ForkNumber {
    MAIN_FORKNUMBER = 0,
    FSM_FORKNUM,
    INIT_FORKNUM,
} ForkNumber;

char* GetRelPath(int rnode, ForkNumber fn);

#endif