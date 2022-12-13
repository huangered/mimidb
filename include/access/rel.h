#ifndef _rel_hpp_
#define _rel_hpp_

#include "mimi.h"
#include "access/tupledesc.h"
#include "catalog/mimi_class.h"
#include "catalog/mimi_attribute.h"
#include "catalog/mimi_index.h"
#include "storage/block.h"
#include "storage/smgr.h"
#include "storage/relfilenode.h"

struct Heap;
struct IndexAm;

struct RelationData {
    SMgrRelation rd_smgr; /* 保存的文件句柄*/
    struct RelFileNode rd_node;  /* relation的物理位置*/

    Oid rd_id;

    Form_mimi_class rd_rel; /* relation 详细描述 */
    TupleDesc tupleDesc;    /* relation tuple 结构描述 */
    int refcount;
    struct Heap* tb_am;
    struct IndexAm* index_am;

    void* rd_metacache; /* meta 缓存对象 */
    Form_mimi_index rd_index;
};

inline BlockNumber
RelationGetTargetBlock(struct RelationData* relation) {
    return relation->rd_smgr != NULL ? relation->rd_smgr->smgr_target_block : INVALID_BLOCK;
}

inline void
RelationSetTargetBlock(struct RelationData* relation, BlockNumber targetblock) {
    RelationOpenSmgr(relation);
    relation->rd_smgr->smgr_target_block = targetblock;
}

#endif