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

class RelationData {
public:
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

public:
    RelationData() {
        rd_smgr = nullptr;
        rd_rel = nullptr;
        rd_tupledesc = nullptr;
        rd_metacache = nullptr;
        rd_index = nullptr;
    }

    ~RelationData() {
    }

    void IncRefCnt() {
        refcount++;
    }
    void DecRefCnt() {
        refcount--;
    }


    BlockNumber RelationGetTargetBlock() {
        return rd_smgr != nullptr ? rd_smgr->smgr_target_block : INVALID_BLOCK;
    }

    void RelationSetTargetBlock(BlockNumber targetblock) {
        RelationOpenSmgr(this);
        rd_smgr->smgr_target_block = targetblock;
    }
};

#endif