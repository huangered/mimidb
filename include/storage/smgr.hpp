#ifndef _smgr_hpp_
#define _smgr_hpp_

#include "storage/block.hpp"
#include "access/relcache.hpp"
#include "access/relpath.hpp"
#include "storage/page.hpp"
#include "storage/relfilenode.hpp"

struct SMgrRelationData {
    RelFileNode rd_node;

    BlockNumber smgr_target_block; /* 当前插入的block */
    BlockNumber smgr_fsm_nblocks;	 /* last known size of fsm fork */

    int fd[INIT_FORKNUM];
};

typedef SMgrRelationData* SMgrRelation;

class Md
{
private:
    int Open(SMgrRelation reln, ForkNumber forknum);
public:
    int Nblock(SMgrRelation reln, ForkNumber forknum);
    int Write(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer);
    int Read(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer);
    void Close(SMgrRelation reln, ForkNumber forknum);
    int Extend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer);
    bool Exist(SMgrRelation reln, ForkNumber forknum);
    void Create(SMgrRelation reln, ForkNumber forknum);
};

class Smgr {
private:
    Md* md;
    HashMap<RelFileNode, SMgrRelation> _data;
public:
    Smgr();
    ~Smgr();
    SMgrRelation Open(RelFileNode rnode);
    bool Exists(SMgrRelation reln, ForkNumber forknum);
    BlockNumber Nblocks(SMgrRelation reln, ForkNumber forknum);
    void Create(SMgrRelation reln, ForkNumber forknum);
    void Read(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf);
    void Write(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf);
    void Extend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf);
    void Close(SMgrRelation reln);
};

extern Smgr* smgr;

// 更上层函数
/*
打开relation的文件
*/
void RelationOpenSmgr(Relation rel);

#endif // !_smgr_h_
