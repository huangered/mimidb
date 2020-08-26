#ifndef _fsm_internal_h_
#define _fsm_internal_h_

#include "access/rel.h"
#include "storage/block.h"
#include "storage/bufmgr.h"

struct FsmAddress {
    int level;
};

struct FSMPageData {
    int items[20];
};

typedef struct FSMPageData* FSMPage;

extern BlockNum fsm_search_avail(Relation rel, Size spaceNeed);
extern void fsm_set_value(Relation rel, BlockNum usedBlock, Size freeSpace);


#endif // !_fsm_internal_h_
