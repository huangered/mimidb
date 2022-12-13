#include "storage/smgr.h"
#include "access/rel.h"
#include "access/relpath.h"
#include "util/hashmap.h"
#include "port/port.h"

bool
Exists(SMgrRelation reln, ForkNumber forknum) {
    return mdexist(reln, forknum);
}

SMgrRelation
Open(struct RelFileNode reln) {
    SMgrRelation rel;
   /* if (_data.Get(reln, &rel))
        return rel;*/

    rel                    = palloc(sizeof(struct SMgrRelationData));
    rel->smgr_target_block = INVALID_BLOCK;
    rel->smgr_fsm_nblocks  = INVALID_BLOCK;
    rel->rd_node           = reln;
    for (int i = 0; i < NUMS_FORKNUM; i++) {
        rel->md_fd[i] = NULL;
    }

    // todo _data.Put(reln, rel);
    return rel;
}

BlockNumber
Nblocks(SMgrRelation reln, ForkNumber forknum) {
    return mdnblocks(reln, forknum);
}

void
Create(SMgrRelation reln, ForkNumber forknum) {
    mdcreate(reln, forknum);
}

void
Read(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer) {
    mdread(reln, forknum, blocknum, buffer);
}

void
Write(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer) {
    mdwrite(reln, forknum, blocknum, buffer);
}

void
Extend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer) {
    mdextend(reln, forknum, blocknum, buffer);
}

void
Close(SMgrRelation reln) {
    for (int i = 0; i < INIT_FORKNUM; i++) {
        mdclose(reln, (ForkNumber)i);
    }
    // _data.Remove(reln->rd_node);
}

// ------
void
RelationOpenSmgr(Relation rel) {
    if (rel->rd_smgr == NULL) {
        // todo rel->rd_smgr = smgr->Open(rel->rd_node);
    }
}
