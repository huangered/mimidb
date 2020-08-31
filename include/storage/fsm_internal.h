#ifndef _fsm_internal_h_
#define _fsm_internal_h_

#include "access/rel.h"
#include "storage/block.h"
#include "storage/bufmgr.h"

#define FSM_CATEGORIES      256

#define FSM_TREE_DEPTH      3
#define FSM_ROOT_LEVEL      (FSM_TREE_DEPTH - 1)
#define FSM_BOTTOM_LEVEL    0

typedef struct FsmAddress {
    int level;      /* level */
    int logpageno;  /* page number in the level */
} FSMAddress;

/* Address of the root page. */
static const FSMAddress FSM_ROOT_ADDRESS = { FSM_ROOT_LEVEL, 0 };

struct FSMPageData {
    int items[20];
};

typedef struct FSMPageData* FSMPage;

extern Buffer fsm_readbuf(Relation rel, FSMAddress addr);
extern BlockNumber fsm_search_avail(Buffer buf, Size spaceNeed);
extern void fsm_set_value(Buffer buf, BlockNumber usedBlock, Size freeSpace);
extern void fsm_extend(Relation rel, BlockNumber blkno);

#endif // !_fsm_internal_h_
