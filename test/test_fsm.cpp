#include "g.h"

_EXTERN_C

#include "storage/fsm_internal.h"
#include "util/mctx.h"
#include "storage/smgr.h"
_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(fsm, root)
{
    RelationData rel;
    rel.rnode = 2000;
    rel.rd_smgr = (SmgrRelation)palloc(sizeof(SMgrRelationData));
    rel.rd_smgr->smgr_fsm_nblocks = 0;
    Buffer buf = fsm_readbuf(&rel, FSM_ROOT_ADDRESS, true);
    printf("buf %d", buf);
}

TEST(fsm, leaf)
{
    FSMAddress addr = { FSM_BOTTOM_LEVEL , 0 };
    Buffer buf = fsm_readbuf(NULL, addr, true);
    printf("buf %d", buf);
}