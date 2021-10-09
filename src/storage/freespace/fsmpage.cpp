#include "storage/fsm_internal.hpp"
#include "storage/smgr.hpp"

#define parentof(X) (((X)-1) / 2)

#define left_children(X)  (2 * (X) + 1)
#define right_children(X) (2 * (X) + 2)


int
fsm_get_avail(Page page, int slot) {
    FSMPage fsmpage = (FSMPage)PageGetContent(page);

    return fsmpage->fp_nodes[NonLeafNodesPerPage + slot];
}

bool
fsm_set_avail(Page page, int slot, int value) {

    int nodeno      = slot + NonLeafNodesPerPage;
    FSMPage fsmpage = (FSMPage)PageGetContent(page);
    int oldvalue;

    oldvalue = fsmpage->fp_nodes[nodeno];

    if (oldvalue == value && value <= fsmpage->fp_nodes[0])
        return false;

    fsmpage->fp_nodes[nodeno] = value;

    do {
        int newvalue = 0;
        int lchild;
        int rchild;

        nodeno = parentof(nodeno);
        lchild = left_children(nodeno);
        rchild = lchild + 1;

        newvalue = fsmpage->fp_nodes[lchild];
        if (rchild < NodesPerPage)
            newvalue = std::max(newvalue, fsmpage->fp_nodes[rchild]);

        oldvalue = fsmpage->fp_nodes[nodeno];
        if (oldvalue == newvalue)
            break;

        fsmpage->fp_nodes[nodeno] = newvalue;
    } while (nodeno > 0);

    return true;
}


int
fsm_search_avail(Buffer buf, uint8 minValue) {
    int no = 0;
    int slot;

    Page page   = BufferGetPage(buf);
    FSMPage fsm = (FSMPage)PageGetContent(page);

    if (fsm->fp_nodes[no] < minValue) {
        return -1;
    }

    while (no < NonLeafNodesPerPage) {
        int left  = left_children(no);
        int right = right_children(no);
        if (fsm->fp_nodes[left] >= minValue) {
            no = left;
        } else if (fsm->fp_nodes[right] >= minValue) {
            no = right;
        }
    }
    slot = no - NonLeafNodesPerPage;

    return slot;
}
