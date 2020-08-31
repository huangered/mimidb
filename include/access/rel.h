#ifndef _REL_H_
#define _REL_H_

#include "mimi.h"
#include "access/relcache.h"
#include "storage/block.h"
#include "access/tbapi.h"
#include "access/amapi.h"
#include "access/tupledesc.h"
#include "catalog/mimi_class.h"
#include "catalog/mimi_attribute.h"

typedef struct RelationData {
    Oid oid;
    int rnode;
    BlockNumber root_blkno;

    Form_mimi_class rd_rel; /* relation tuple */
    TupleDesc tupleDesc;    /* retuple descriptor */
    int refcount;
    TableAmRoute* tb_am;
    IndexAmRoute* index_am;

    struct SMgrRelationData* rd_smgr;
} RelationData;


#endif