#ifndef _fsm_internal_h_
#define _fsm_internal_h_

#include "access/rel.hpp"
#include "storage/block.hpp"
#include "storage/bufmgr.hpp"

#define FSM_CATEGORIES 256

#define FSM_TREE_DEPTH 3
#define FSM_ROOT_LEVEL (FSM_TREE_DEPTH - 1)
#define FSM_BOTTOM_LEVEL 0

#define FLEXIBLE_ARRAY_MEMBER

#define NodesPerPage 7
#define NonLeafNodesPerPage 3
#define LeafNodesPerPage (NodesPerPage - NonLeafNodesPerPage)

typedef struct FsmAddress {
    int level;     /* level */
    int logpageno; /* page number in the level */
} FSMAddress;

/* Address of the root page. */
static const FSMAddress FSM_ROOT_ADDRESS = {FSM_ROOT_LEVEL, 0};

struct FSMPageData {
    int fp_next_slot;
    int fp_nodes[FLEXIBLE_ARRAY_MEMBER];
};

typedef struct FSMPageData* FSMPage;

class fsm {
public:
    Buffer fsm_readbuf(Relation rel, FSMAddress addr, bool extend);
    BlockNumber fsm_search(Relation rel, Size spaceNeed);
    int fsm_search_avail(Buffer buf, Size spaceNeed);
    int fsm_get_avail(Page page, int slot);
    bool fsm_set_avail(Page page, int slot, int value);
    void fsm_extend(Relation rel, BlockNumber blkno);
    int fsm_set_and_search(Relation rel, FSMAddress addr, int slot, int newValue, int minValue);
    FSMAddress fsm_get_location(BlockNumber heapblk, int* slot);
    int fsm_vacuum_page(Relation rel, FSMAddress addr, BlockNumber start, BlockNumber end);

private:
    BlockNumber fsm_logic_to_physical(FSMAddress addr);
    BlockNumber fsm_get_heap_blk(FSMAddress addr, int slot);
    FSMAddress fsm_get_child(FSMAddress addr, int slot);
    FSMAddress fsm_get_parent(FSMAddress child, int* slot);
};
#endif // !_fsm_internal_h_
