#include "g.h"

_EXTERN_C

#include "storage/fsm_internal.h"

_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(fsm, root)
{
    Buffer buf = fsm_readbuf(NULL, FSM_ROOT_ADDRESS, true);
    printf("buf %d", buf);
}

TEST(fsm, leaf)
{
    FSMAddress addr = { FSM_BOTTOM_LEVEL , 0 };
    Buffer buf = fsm_readbuf(NULL, addr, true);
    printf("buf %d", buf);
}