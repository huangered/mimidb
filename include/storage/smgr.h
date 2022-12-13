﻿#ifndef _smgr_hpp_
#define _smgr_hpp_

#include "storage/block.h"
#include "access/relcache.h"
#include "access/relpath.h"
#include "storage/page.h"
#include "storage/relfilenode.h"

struct SMgrRelationData {
    struct RelFileNode rd_node;

    BlockNumber smgr_target_block; /* 当前插入的block */
    BlockNumber smgr_fsm_nblocks;  /* last known size of fsm fork */

    struct _MdFdVec* md_fd[NUMS_FORKNUM];
};

typedef struct SMgrRelationData* SMgrRelation;

SMgrRelation Open(struct RelFileNode rnode);
bool Exists(SMgrRelation reln, ForkNumber forknum);
BlockNumber Nblocks(SMgrRelation reln, ForkNumber forknum);
void Create(SMgrRelation reln, ForkNumber forknum);
void Read(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf);
void Write(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf);
void Extend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf);
void Close(SMgrRelation reln);

// 更上层函数
/*
打开relation的文件
*/
void RelationOpenSmgr(Relation rel);

// private md method
bool mdexist(SMgrRelation reln, ForkNumber forknum);
void mdcreate(SMgrRelation reln, ForkNumber forknum);
void mdread(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf);
void mdwrite(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf);
BlockNumber mdnblocks(SMgrRelation reln, ForkNumber forknum);
void mdextend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf);
void mdclose(SMgrRelation reln, ForkNumber forknum);
#endif // !_smgr_h_
