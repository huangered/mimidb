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

/*
  在 slot 上赋值，如果有改动，返回 true
 */
bool
fsm_set_avail(Page page, int slot, uint8 value) {

    int nodeno      = slot + NonLeafNodesPerPage;
    FSMPage fsmpage = (FSMPage)PageGetContent(page);
    int oldvalue;

    oldvalue = fsmpage->fp_nodes[nodeno];

    if (oldvalue == value && value <= fsmpage->fp_nodes[0])
        return false;

    fsmpage->fp_nodes[nodeno] = value;

    /*
     * 向上传播，如果不需要更新或遇到 root 节点，停止
     */
    do {
        uint8 newvalue = 0;
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

    if (value > fsmpage->fp_nodes[0]) {
        fsm_rebuild_page(page);
    }

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

bool
fsm_rebuild_page(Page page) {
    FSMPage fsmpage = (FSMPage)PageGetContent(page);
    bool changed    = false;
    int nodeno;

	/*
     * Start from the lowest non-leaf level, at last node, working our way
     * backwards, through all non-leaf nodes at all levels, up to the root.
     */
    for (nodeno = NonLeafNodesPerPage - 1; nodeno >= 0; nodeno--) {
        int lchild     = left_children(nodeno);
        int rchild     = lchild + 1;
        uint8 newvalue = 0;

        /* The first few nodes we examine might have zero or one child. */
        if (lchild < NodesPerPage)
            newvalue = fsmpage->fp_nodes[lchild];

        if (rchild < NodesPerPage)
            newvalue = std::max(newvalue, fsmpage->fp_nodes[rchild]);

        if (fsmpage->fp_nodes[nodeno] != newvalue) {
            fsmpage->fp_nodes[nodeno] = newvalue;
            changed                   = true;
        }
    }

    return changed;
}
