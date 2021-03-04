#include "storage/fsm_internal.hpp"
#include "storage/smgr.hpp"

#define parentof(X)         (((X) - 1) / 2 )

#define left_children(X)    ( 2 * (X) + 1 )
#define right_children(X)   ( 2 * (X) + 2 )

static BlockNumber fsm_logic_to_physical(FSMAddress addr);

static BlockNumber fsm_get_heap_blk(FSMAddress addr, int slot);
static FSMAddress fsm_get_child(FSMAddress addr, int slot);
static FSMAddress fsm_get_parent(FSMAddress child, int* slot);
/*
1. find a available block
2. if no block find , fsm_extend new page and search again
*/
Buffer
fsm::fsm_readbuf(Relation rel, FSMAddress addr, bool extend) {
    BlockNumber blkno = fsm_logic_to_physical(addr);
    Buffer      buf;

    // open smgr of rel

    // if exist rel fsm file
    if (rel->rd_smgr->smgr_fsm_nblocks == INVALID_BLOCK ||
        blkno >= rel->rd_smgr->smgr_fsm_nblocks) {
        if (smgrexists(rel, FSM_FORKNUM)) {
            rel->rd_smgr->smgr_fsm_nblocks = smgrblocks(rel, FSM_FORKNUM);
        }
        else {
            rel->rd_smgr->smgr_fsm_nblocks = 0;
        }
    }

    if (blkno >= rel->rd_smgr->smgr_fsm_nblocks) {
        if (extend) {
            fsm_extend(rel, blkno + 1);
        }
        else {
            return INVALID_BUFFER;
        }
    }

    buf = ReadBuffer(rel, FSM_FORKNUM, blkno);
    if (PageIsNew(BufferGetPage(buf))) {
        PageInit(BufferGetPage(buf), BLKSZ, 0);
    }

    return buf;
}

BlockNumber
fsm::fsm_search(Relation rel, Size spaceNeed) {
    FSMAddress address = FSM_ROOT_ADDRESS;

    for (;;) {
        int slot;
        Buffer buf;

        buf = fsm_readbuf(rel, address, false);

        if (BufferIsValid(buf)) {
            slot = fsm_search_avail(buf, spaceNeed);
        }
        else
            slot = -1;

        if (slot != -1) {
            if (address.level == FSM_BOTTOM_LEVEL)
                return fsm_get_heap_blk(address, slot);

            address = fsm_get_child(address, slot);
        }
        else if (address.level == FSM_ROOT_LEVEL) {
            /*
            at the root, failure means there is no enough space, return invalid.
            */
            return INVALID_BLOCK;
        }
        else {
            // create new fsm page
            int parentslot;
            FSMAddress parent;

            parent = fsm_get_parent(address, &parentslot);
            fsm_set_and_search(rel, parent, parentslot, BLKSZ, 0);

            address = FSM_ROOT_ADDRESS;
        }
    }

    return INVALID_BLOCK;
}

int
fsm::fsm_get_avail(Page page, int slot) {
    FSMPage fsmpage = (FSMPage)PageGetContent(page);


    return fsmpage->fp_nodes[NonLeafNodesPerPage + slot];
}

bool
fsm::fsm_set_avail(Page page, int slot, int value) {
    
    int nodeno = slot + NonLeafNodesPerPage;
    FSMPage fsmpage = (FSMPage)PageGetContent(page);
    int oldvalue;

    oldvalue = fsmpage->fp_nodes[nodeno];

    if (oldvalue == value && value <= fsmpage->fp_nodes[0])
        return false;

    fsmpage->fp_nodes[nodeno] = value;

    do
    {
        int newvalue = 0;
        int lchild;
        int rchild;

        nodeno = parentof(nodeno);
        lchild = left_children(nodeno);
        rchild = lchild + 1;

        newvalue = fsmpage->fp_nodes[lchild];
        if (rchild < NodesPerPage)
            newvalue = Max(newvalue,
                fsmpage->fp_nodes[rchild]);

        oldvalue = fsmpage->fp_nodes[nodeno];
        if (oldvalue == newvalue)
            break;

        fsmpage->fp_nodes[nodeno] = newvalue;
    } while (nodeno > 0);

    return true;
}

typedef struct PgData {
    char data[BLKSZ];
} PgData;

void
fsm::fsm_extend(Relation rel, BlockNumber blkno) {
    PgData data;
    PageInit((Page)data.data, BLKSZ, 0);

    BlockNumber fsm_blocks = smgrblocks(rel, FSM_FORKNUM);
    while (fsm_blocks < blkno) {
        smgrextend(rel, (Page)data.data, fsm_blocks, FSM_FORKNUM);
        fsm_blocks++;
    }
    rel->rd_smgr->smgr_fsm_nblocks = fsm_blocks;
}

int
fsm::fsm_search_avail(Buffer buf, Size spaceNeed) {
    int no = 0;
    int slot;

    Page page = BufferGetPage(buf);
    FSMPage fsm = (FSMPage)PageGetContent(page);

    if (fsm->fp_nodes[no] < spaceNeed) {
        return -1;
    }

    while (no < NonLeafNodesPerPage) {
        int left = left_children(no);
        int right = right_children(no);
        if (fsm->fp_nodes[left] >= spaceNeed) {
            no = left;
        }
        else if (fsm->fp_nodes[right] >= spaceNeed) {
            no = right;
        }
    }
    slot = no - NonLeafNodesPerPage;

    return slot;
}

// private methods
BlockNumber
fsm::fsm_logic_to_physical(FSMAddress addr) {
    BlockNumber pages;
    int         leafno;
    int         l;

    leafno = addr.logpageno;
    for (l = 0; l < addr.level; l++) {
        leafno *= LeafNodesPerPage;
    }

    pages = 0;
    for (l = 0; l < FSM_TREE_DEPTH; l++) {
        pages += leafno + 1;
        leafno /= LeafNodesPerPage;
    }

    pages -= addr.level;
    return pages - 1;
}

/*
get real block number
*/
BlockNumber
fsm::fsm_get_heap_blk(FSMAddress addr, int slot) {
    return addr.logpageno * LeafNodesPerPage + slot;
}
FSMAddress
fsm::fsm_get_child(FSMAddress addr, int slot) {
    FSMAddress child;
    child.level = addr.level - 1;
    child.logpageno = addr.logpageno * LeafNodesPerPage + slot;
    return child;
}

FSMAddress
fsm::fsm_get_parent(FSMAddress child, int* slot) {
    FSMAddress parent;

    parent.level = child.level + 1;
    parent.logpageno = child.logpageno / LeafNodesPerPage;
    *slot = child.logpageno % LeafNodesPerPage;

    return parent;
}

int
fsm::fsm_set_and_search(Relation rel, FSMAddress addr, int slot,
    int newValue, int minValue) {
    Buffer buf;
    Page page;
    int newslot = -1;

    buf = fsm_readbuf(rel, addr, true);
    page = BufferGetPage(buf);

    fsm_set_avail(page, slot, newValue);

    return newslot;
}

FSMAddress
fsm::fsm_get_location(BlockNumber heapblk, int* slot) {
    FSMAddress	addr;

    addr.level = FSM_BOTTOM_LEVEL;
    addr.logpageno = heapblk / LeafNodesPerPage;
    *slot = heapblk % LeafNodesPerPage;

    return addr;
}

int
fsm::fsm_vacuum_page(Relation rel, FSMAddress addr, BlockNumber start, BlockNumber end) {
    Buffer buf;
    Page page;
    int max_avail = 0;

    /* read the buf */
    buf = fsm_readbuf(rel, addr, false);
    if (BufferIsInvalid(buf)) {
        return 0;
    }

    page = BufferGetPage(buf);

    if (addr.level > FSM_BOTTOM_LEVEL) {
        FSMAddress fsm_start,
                   fsm_end;
        int fsm_start_slot,
            fsm_end_slot;
        int slot,
            start_slot,
            end_slot;
        bool eof = false;

        /*
         * Compute the range of slots we need to update on this page, given
         * the requested range of heap blocks to consider.  The first slot to
         * update is the one covering the "start" block, and the last slot is
         * the one covering "end - 1".  (Some of this work will be duplicated
         * in each recursive call, but it's cheap enough to not worry about.)
         */
        fsm_start = fsm_get_location(start, &fsm_start_slot);
        fsm_end = fsm_get_location(end - 1, &fsm_end_slot);

        while (fsm_start.level < addr.level)
        {
            fsm_start = fsm_get_parent(fsm_start, &fsm_start_slot);
            fsm_end = fsm_get_parent(fsm_end, &fsm_end_slot);
        }

        if (fsm_start.logpageno == addr.logpageno)
            start_slot = fsm_start_slot;
        else if (fsm_start.logpageno > addr.logpageno)
            start_slot = LeafNodesPerPage;	/* shouldn't get here... */
        else
            start_slot = 0;

        if (fsm_end.logpageno == addr.logpageno)
            end_slot = fsm_end_slot;
        else if (fsm_end.logpageno > addr.logpageno)
            end_slot = LeafNodesPerPage - 1;
        else
            end_slot = -1;		/* shouldn't get here... */

        for (slot = start_slot; slot <= end_slot; slot++)
        {
            int			child_avail;

            /* After we hit end-of-file, just clear the rest of the slots */
            if (!eof)
                child_avail = fsm_vacuum_page(rel, fsm_get_child(addr, slot),
                    start, end);
            else
                child_avail = 0;

            /* Update information about the child */
            if (fsm_get_avail(page, slot) != child_avail)
            {
                fsm_set_avail(page, slot, child_avail);
            }
        }
    }

    FSMPage fsmpage = (FSMPage)PageGetContent(page);

    max_avail = fsmpage->fp_nodes[0];

    return max_avail;
}