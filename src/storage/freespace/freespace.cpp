﻿#include "storage/freespace.hpp"
#include "storage/fsm_internal.hpp"
#include "storage/page.hpp"

// cat 是 catagory 缩写

#define FSM_CATAGORIES 256
#define FSM_CAT_STEP   (BLKSZ / FSM_CATAGORIES)

#define FSM_TREE_DEPTH   3
#define FSM_ROOT_LEVEL   (FSM_TREE_DEPTH - 1)
#define FSM_BOTTOM_LEVEL 0

typedef struct {
    int level;     /* level */
    int logpageno; /* page number in the level */
} FSMAddress;

/* Address of the root page. */
static const FSMAddress FSM_ROOT_ADDRESS = { FSM_ROOT_LEVEL, 0 };

static Buffer fsm_readbuf(Relation rel, FSMAddress addr, bool extend);
static BlockNumber fsm_search(Relation rel, uint8 cat);
static void fsm_extend(Relation rel, BlockNumber blkno);
static int fsm_set_and_search(Relation rel, FSMAddress addr, int slot, int newValue, int minValue);
static int fsm_vacuum_page(Relation rel, FSMAddress addr, BlockNumber start, BlockNumber end);

// fsm 树导航函数
static FSMAddress fsm_get_child(FSMAddress addr, int slot);
static FSMAddress fsm_get_parent(FSMAddress child, int* slot);
static FSMAddress fsm_get_location(BlockNumber heapblk, int* slot);
static BlockNumber fsm_logic_to_physical(FSMAddress addr);
static BlockNumber fsm_get_heap_blk(FSMAddress addr, int slot);

// 辅助转换函数
static uint8 fsm_space_avail_to_cat(Size avail);
static Size fsm_space_cat_to_avail(uint8 cat);

/** public method **/
BlockNumber
GetPageWithFreeSpace(Relation rel, Size spaceNeeded) {
    int min_cat = fsm_space_avail_to_cat(spaceNeeded);

    return fsm_search(rel, min_cat);
}

void
RecordPageWithFreeSpace(Relation rel, BlockNumber usedBlock, Size freeSpace) {
    int new_cat = fsm_space_avail_to_cat(freeSpace);
    FSMAddress addr;
    int slot = 0;

    addr = fsm_get_location(usedBlock, &slot);
    fsm_set_and_search(rel, addr, slot, new_cat, 0);
}

BlockNumber
RecordAndGetPageWithFreeSpace(Relation rel, BlockNumber oldPage, Size oldSpaceAvail, Size spaceNeeded) {
    int old_cat   = fsm_space_avail_to_cat(oldSpaceAvail);
    int space_cat = fsm_space_avail_to_cat(spaceNeeded);
    FSMAddress addr;
    int slot;
    int search_slot;

    addr = fsm_get_location(oldPage, &slot);

    search_slot = fsm_set_and_search(rel, addr, slot, space_cat, old_cat);

    if (search_slot != -1) {
        return fsm_get_heap_blk(addr, search_slot);
    } else {
        return fsm_search(rel, space_cat);
    }
}

void
FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end) {
    if (end > start) {
        fsm_vacuum_page(rel, FSM_ROOT_ADDRESS, start, end);
    }
}

void
FreeSpaceMapVacuum(Relation rel) {
}

/** private api **/
static uint8
fsm_space_avail_to_cat(Size avail) {
    int cat;

    cat = avail / FSM_CAT_STEP;

    if (cat > 254) {
        cat = 254;
    }
    return (uint8)cat;
}

static Size
fsm_space_cat_to_avail(uint8 cat) {
    return cat * FSM_CAT_STEP;
}

/*
1. find a available block
2. if no block find , fsm_extend new page and search again
*/
static Buffer
fsm_readbuf(Relation rel, FSMAddress addr, bool extend) {
    BlockNumber blkno = fsm_logic_to_physical(addr);
    Buffer buf;

    // open smgr of rel
    RelationOpenSmgr(rel);

    // if exist rel fsm file
    if (rel->rd_smgr->smgr_fsm_nblocks == INVALID_BLOCK || blkno >= rel->rd_smgr->smgr_fsm_nblocks) {
        if (smgr->Exists(rel->rd_smgr, FSM_FORKNUM)) {
            rel->rd_smgr->smgr_fsm_nblocks = smgr->Nblocks(rel->rd_smgr, FSM_FORKNUM);
        } else {
            rel->rd_smgr->smgr_fsm_nblocks = 0;
        }
    }

    if (blkno >= rel->rd_smgr->smgr_fsm_nblocks) {
        if (extend) {
            fsm_extend(rel, blkno + 1);
        } else {
            return INVALID_BUFFER;
        }
    }

    buf = ReadBufferExtend(rel, FSM_FORKNUM, blkno);
    if (PageIsNew(BufferGetPage(buf))) {
        PageInit(BufferGetPage(buf), BLKSZ, 0);
    }

    return buf;
}

static BlockNumber
fsm_search(Relation rel, uint8 min_cat) {
    FSMAddress address = FSM_ROOT_ADDRESS;

    for (;;) {
        int slot;
        Buffer buf;

        buf = fsm_readbuf(rel, address, false);

        if (BufferIsValid(buf)) {
            slot = fsm_search_avail(buf, min_cat);
        } else
            slot = -1;

        if (slot != -1) {
            if (address.level == FSM_BOTTOM_LEVEL)
                return fsm_get_heap_blk(address, slot);

            address = fsm_get_child(address, slot);
        } else if (address.level == FSM_ROOT_LEVEL) {
            /*
            at the root, failure means there is no enough space, return invalid.
            */
            return INVALID_BLOCK;
        } else {
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

typedef struct PgData {
    char data[BLKSZ];
} PgData;

static void
fsm_extend(Relation rel, BlockNumber blkno) {
    PgData data;
    PageInit((Page)data.data, BLKSZ, 0);
    BlockNumber fsm_blocks = smgr->Nblocks(rel->rd_smgr, FSM_FORKNUM);
    while (fsm_blocks < blkno) {
        smgr->Extend(rel->rd_smgr, FSM_FORKNUM, fsm_blocks, (Page)data.data);
        fsm_blocks++;
    }
    rel->rd_smgr->smgr_fsm_nblocks = fsm_blocks;
}

static BlockNumber
fsm_logic_to_physical(FSMAddress addr) {
    BlockNumber pages;
    int leafno;
    int l;

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
static BlockNumber
fsm_get_heap_blk(FSMAddress addr, int slot) {
    return addr.logpageno * LeafNodesPerPage + slot;
}

static FSMAddress
fsm_get_child(FSMAddress addr, int slot) {
    FSMAddress child;
    child.level     = addr.level - 1;
    child.logpageno = addr.logpageno * LeafNodesPerPage + slot;
    return child;
}

static FSMAddress
fsm_get_parent(FSMAddress child, int* slot) {
    FSMAddress parent;

    parent.level     = child.level + 1;
    parent.logpageno = child.logpageno / LeafNodesPerPage;
    *slot            = child.logpageno % LeafNodesPerPage;

    return parent;
}

static int
fsm_set_and_search(Relation rel, FSMAddress addr, int slot, int newValue, int minValue) {
    Buffer buf;
    Page page;
    int newslot = -1;

    buf  = fsm_readbuf(rel, addr, true);
    page = BufferGetPage(buf);

    fsm_set_avail(page, slot, newValue);

    return newslot;
}

static FSMAddress
fsm_get_location(BlockNumber heapblk, int* slot) {
    FSMAddress addr;

    addr.level     = FSM_BOTTOM_LEVEL;
    addr.logpageno = heapblk / LeafNodesPerPage;
    *slot          = heapblk % LeafNodesPerPage;

    return addr;
}

static int
fsm_vacuum_page(Relation rel, FSMAddress addr, BlockNumber start, BlockNumber end) {
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
        FSMAddress fsm_start, fsm_end;
        int fsm_start_slot, fsm_end_slot;
        int slot, start_slot, end_slot;
        bool eof = false;

        /*
         * Compute the range of slots we need to update on this page, given
         * the requested range of heap blocks to consider.  The first slot to
         * update is the one covering the "start" block, and the last slot is
         * the one covering "end - 1".  (Some of this work will be duplicated
         * in each recursive call, but it's cheap enough to not worry about.)
         */
        fsm_start = fsm_get_location(start, &fsm_start_slot);
        fsm_end   = fsm_get_location(end - 1, &fsm_end_slot);

        while (fsm_start.level < addr.level) {
            fsm_start = fsm_get_parent(fsm_start, &fsm_start_slot);
            fsm_end   = fsm_get_parent(fsm_end, &fsm_end_slot);
        }

        if (fsm_start.logpageno == addr.logpageno)
            start_slot = fsm_start_slot;
        else if (fsm_start.logpageno > addr.logpageno)
            start_slot = LeafNodesPerPage; /* shouldn't get here... */
        else
            start_slot = 0;

        if (fsm_end.logpageno == addr.logpageno)
            end_slot = fsm_end_slot;
        else if (fsm_end.logpageno > addr.logpageno)
            end_slot = LeafNodesPerPage - 1;
        else
            end_slot = -1; /* shouldn't get here... */

        for (slot = start_slot; slot <= end_slot; slot++) {
            int child_avail;

            /* After we hit end-of-file, just clear the rest of the slots */
            if (!eof)
                child_avail = fsm_vacuum_page(rel, fsm_get_child(addr, slot), start, end);
            else
                child_avail = 0;

            /* Update information about the child */
            if (fsm_get_avail(page, slot) != child_avail) {
                fsm_set_avail(page, slot, child_avail);
            }
        }
    }

    FSMPage fsmpage = (FSMPage)PageGetContent(page);

    max_avail = fsmpage->fp_nodes[0];

    return max_avail;
}
