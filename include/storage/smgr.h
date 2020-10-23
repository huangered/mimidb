#ifndef _smgr_h_
#define _smgr_h_

#include "storage/block.h"
#include "access/relcache.h"
#include "access/relpath.h"
#include "storage/page.h"
#include "storage/relnode.h"

typedef struct SMgrRelationData {
    BlockNumber smgr_fsm_nblocks;	/* last known size of fsm fork */
} SMgrRelationData;

typedef SMgrRelationData* SmgrRelation;

extern bool smgrexists(RelFileNode rel, ForkNumber number);
extern void smgrcreate(RelFileNode rel, ForkNumber number);
extern BlockNumber smgrblocks(RelFileNode rel, ForkNumber number);
extern void smgrextend(RelFileNode rel, Page page, BlockNumber blkno, ForkNumber number);
extern void smgrwrite(RelFileNode rel, ForkNumber number, BlockNumber blkno, const char* buf);
#endif // !_smgr_h_
