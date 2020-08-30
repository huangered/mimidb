#ifndef _fsm_internal_h_
#define _fsm_internal_h_

#include "access/rel.h"
#include "storage/block.h"
#include "storage/bufmgr.h"

typedef struct FsmAddress {
    int level;
    int block;
} FSMAddress;

struct FSMPageData {
    int items[20];
};

typedef struct FSMPageData* FSMPage;

BlockNum fsm_search_avail(Buffer buf, Size spaceNeed);
void fsm_set_value(Buffer buf, BlockNum usedBlock, Size freeSpace);
void fsm_extend();
#endif // !_fsm_internal_h_
