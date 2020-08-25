#ifndef _REL_H_
#define _REL_H_

#include "mimi.h"
#include "access/relcache.h"
#include "storage/block.h"
#include "access/tbapi.h"
#include "access/amapi.h"
#include "access/tupledesc.h"
#include "catalog/mimi_attribute.h"

typedef struct RelationData {
    Oid oid;
    int rnode;
    BlockNum root_blkno;
    char* name;
    TupleDesc tupleDesc;

    TableAmRoute* tb_am;
    IndexAmRoute* index_am;
} RelationData;


#endif