#ifndef _REL_H_
#define _REL_H_

#include "mimi.hpp"
#include "access/relcache.hpp"
#include "storage/block.hpp"
#include "access/tbapi.hpp"
#include "access/amapi.hpp"
#include "access/tupledesc.hpp"
#include "catalog/mimi_class.hpp"
#include "catalog/mimi_attribute.hpp"

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