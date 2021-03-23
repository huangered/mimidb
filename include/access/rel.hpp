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
#include "storage/smgr.hpp"
#include "storage/relfilenode.hpp"

struct RelationData {
    Oid rd_id;
    BlockNumber root_blkno;

    Form_mimi_class rd_rel; /* relation tuple */
    TupleDesc tupleDesc;    /* retuple descriptor */
    int refcount;
    BaseIndex* tb_am;
    BaseIndex* index_am;

    SMgrRelation rd_smgr; /*保存的文件句柄*/
    RelFileNode rd_node;  /*relation的物理位置*/
    void* rd_metacache;          /*meta对象*/
};

class relation {
private:
    SMgrRelation rd_smgr;
public:
    relation();
    // 更上层函数
    void OpenSmgr();
};

#endif