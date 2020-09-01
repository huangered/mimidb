#ifndef _smgr_h_
#define _smgr_h_

#include "storage/block.h"
#include "access/relcache.h"
#include "access/relpath.h"
#include "storage/page.h"

typedef struct SMgrRelationData {
    BlockNumber smgr_fsm_nblocks;	/* last known size of fsm fork */
} SMgrRelationData;

typedef SMgrRelationData* SmgrRelation;

extern bool smgrexists(Relation rel, ForkNumber number);
extern BlockNumber smgrblocks(Relation rel, ForkNumber number);
extern void smgrextend(Relation rel, Page page, BlockNumber blkno, ForkNumber number);
#endif // !_smgr_h_
