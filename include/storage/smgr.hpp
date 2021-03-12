#ifndef _smgr_h_
#define _smgr_h_

#include "storage/block.hpp"
#include "access/relcache.hpp"
#include "access/relpath.hpp"
#include "storage/page.hpp"

struct SMgrRelationData {
    BlockNumber smgr_target_nblocks; /*最后读取的block*/
    BlockNumber smgr_fsm_nblocks;	/* last known size of fsm fork */
};

typedef SMgrRelationData* SMgrRelation;

SMgrRelation smgropen(Relation rel, ForkNumber number);
bool smgrexists(Relation rel, ForkNumber number);
void smgrcreate(Relation rel, ForkNumber number);
BlockNumber smgrblocks(Relation rel, ForkNumber number);
void smgrextend(Relation rel, Page page, BlockNumber blkno, ForkNumber number);
void smgrwrite(Relation rel, ForkNumber number, BlockNumber blkno, char* buf);
void smgrread(Relation rel, ForkNumber number, BlockNumber blkno, char* buf);

// 更上层函数
/*
打开relation的文件
*/
void RelationOpenSmgr(Relation rel, SMgrRelation reln);

#endif // !_smgr_h_
