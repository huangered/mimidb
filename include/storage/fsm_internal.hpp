#ifndef _fsm_internal_h_
#define _fsm_internal_h_

#include "access/rel.hpp"
#include "storage/block.hpp"
#include "storage/bufmgr.hpp"

struct FSMPageData {
    int fp_next_slot;
    uint8 fp_nodes[1]; // 对象是8位
};

typedef struct FSMPageData* FSMPage;

#define NodesPerPage        (BLKSZ - SizeOfPageHeaderData - offsetof(struct FSMPageData, fp_nodes))
#define NonLeafNodesPerPage (BLKSZ / 2 - 1)
#define LeafNodesPerPage    (NodesPerPage - NonLeafNodesPerPage)

#define SlotsPerFSMPage LeafNodesPerPage

int fsm_search_avail(Buffer buf, uint8 minValue);
int fsm_get_avail(Page page, int slot);
bool fsm_set_avail(Page page, int slot, uint8 value);
bool fsm_rebuild_page(Page page);

#endif // !_fsm_internal_h_
