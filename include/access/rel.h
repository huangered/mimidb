#ifndef _REL_H_
#define _REL_H_

#include "mimi.h"
#include "access/relcache.h"
#include "storage/block.h"
#include "access/tbapi.h"
#include "access/amapi.h"

typedef struct RelationData {
    Oid oid;
    int rnode;
    BlockNum root_blkno;

    TableAmRoute* tb_am;
    IndexAmRoute* index_am;
} RelationData;


#endif