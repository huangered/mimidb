#ifndef _REL_H_
#define _REL_H_

#include "mimi.h"
#include "access/relcache.h"
#include "storage/block.h"
#include "access/tbapi.h"

typedef struct RelationData {
    Oid oid;
    int rnode;
    BlockNum root_blkno;

    TableAmRoute* tb_am;
} RelationData;


#endif