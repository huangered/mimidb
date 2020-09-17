#include "../g.h"

_EXTERN_C
#include "storage/bufmgr.h"
#include "storage/fsm_internal.h"
#include "storage/freespace.h"
#include "util/mctx.h"
#include "storage/smgr.h"
_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(fsm, root)
{
    BufferInit();
    RelationData rel;
    rel.rnode = 2000;
    rel.rd_smgr = (SmgrRelation)palloc(sizeof(SMgrRelationData));
    rel.rd_smgr->smgr_fsm_nblocks = 0;
   // Buffer buf = fsm_readbuf(&rel, FSM_ROOT_ADDRESS, true);
  //  printf("buf %d", buf);
}

TEST(fsm, leaf)
{
    BufferInit();
    RelationData rel;
    rel.rnode = 2000;
    rel.rd_smgr = (SmgrRelation)palloc(sizeof(SMgrRelationData));
    rel.rd_smgr->smgr_fsm_nblocks = 0;
    RecordPageWithFreeSpace(&rel, 0, BLKSZ);
    FreeSpaceMapVacuumRange(&rel, 0, 1);
    BlockNumber blk = fsm_search(&rel, 1024);
    EXPECT_EQ(blk, 0);
}