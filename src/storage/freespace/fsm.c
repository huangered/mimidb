#include "storage/fsm_internal.h"
#include "storage/smgr.h"

static BlockNumber fsm_logic_to_physical(FSMAddress addr);

/*
1. find a available block
2. if no block find , fsm_extend new page and search again
*/
Buffer
fsm_readbuf(Relation rel, FSMAddress addr, bool extend) {
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

    return INVALID_BUFFER;
}

BlockNumber fsm_search_avail(Buffer buf, Size spaceNeed) {
    Page page = BufferGetPage(buf);
    FSMPage fsm = (FSMPage)PageGetContent(page);

    for (int i = 1; i < 100; i++) {
        if (fsm->fp_nodes[i] > spaceNeed) {
            return i;
        }
    }

    return INVALID_BLOCK;
}

void fsm_set_value(Relation rel, BlockNumber usedBlock, Size freeSpace) {
    Buffer buf;
    FSMAddress addr;
    buf = fsm_readbuf(rel, addr, true); 
    Page page = BufferGetPage(buf);
    FSMPage fsm = (FSMPage)PageGetContent(page);
    fsm->fp_nodes[usedBlock] = freeSpace;
}

void
fsm_extend(Relation rel, BlockNumber blkno) {

}

// private methods
BlockNumber
fsm_logic_to_physical(FSMAddress addr) {
    BlockNumber pages;
    int         leafno;
    int         l;

    leafno = addr.logpageno;
    for (l = 0; l < addr.level; l++) {
        leafno *= 4;
    }

    pages = 0;
    for (l = 0; l < FSM_TREE_DEPTH; l++) {
        pages += leafno + 1;
        leafno /= 4;
    }

    pages -= addr.level;
    return pages - 1;
}