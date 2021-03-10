#ifndef _smgr_h_
#define _smgr_h_

#include "storage/block.hpp"
#include "access/relcache.hpp"
#include "access/relpath.hpp"
#include "storage/page.hpp"

typedef struct SMgrRelationData {
    BlockNumber smgr_fsm_nblocks;	/* last known size of fsm fork */
} SMgrRelationData;

typedef SMgrRelationData* SmgrRelation;

void smgropen(Relation rel, ForkNumber number);
bool smgrexists(Relation rel, ForkNumber number);
void smgrcreate(Relation rel, ForkNumber number);
BlockNumber smgrblocks(Relation rel, ForkNumber number);
void smgrextend(Relation rel, Page page, BlockNumber blkno, ForkNumber number);
void smgrwrite(Relation rel, ForkNumber number, BlockNumber blkno, char* buf);
void smgrread(Relation rel, ForkNumber number, BlockNumber blkno, char* buf);
#endif // !_smgr_h_
