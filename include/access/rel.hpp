#ifndef _rel_hpp_
#define _rel_hpp_

#include "mimi.hpp"
#include "access/tupledesc.hpp"
#include "catalog/mimi_class.hpp"
#include "catalog/mimi_attribute.hpp"
#include "catalog/mimi_index.hpp"
#include "storage/block.hpp"
#include "storage/smgr.hpp"
#include "storage/relfilenode.hpp"

class Heap;
class IndexAm;

struct RelationData {
    SMgrRelation rd_smgr; /* 保存的文件句柄*/
    RelFileNode rd_node;  /* relation的物理位置*/

    Oid rd_id;

    Form_mimi_class rd_rel; /* relation 详细描述 */
    TupleDesc rd_tupledesc;    /* relation tuple 结构描述 */
    int refcount;
    Heap* tb_am;
    IndexAm* index_am;

    void* rd_metacache;   /* meta 缓存对象 */
    Form_mimi_index rd_index;
};

inline BlockNumber RelationGetTargetBlock(Relation relation) {
    return relation->rd_smgr != nullptr ? relation->rd_smgr->smgr_target_block : INVALID_BLOCK;
}

inline void RelationSetTargetBlock(Relation relation, BlockNumber targetblock) {
    RelationOpenSmgr(relation);
    relation->rd_smgr->smgr_target_block = targetblock;
}

#endif