#include "storage/smgr.hpp"
#include "access/rel.hpp"
#include "access/relpath.hpp"
#include "util/hashmap.hpp"
#include "port/port.hpp"

Smgr* smgr = new Smgr{};

Smgr::Smgr() {
}

Smgr::~Smgr() {
    auto values = _data.Values();
    for (auto v : values) {
        delete v;
    }
}

bool
Smgr::Exists(SMgrRelation reln, ForkNumber forknum) {
    return mdexist(reln, forknum);
}

SMgrRelation
Smgr::Open(RelFileNode reln) {
    SMgrRelation rel;
    if (_data.Get(reln, &rel))
        return rel;

    rel                    = new SMgrRelationData{};
    rel->smgr_target_block = INVALID_BLOCK;
    rel->smgr_fsm_nblocks  = INVALID_BLOCK;
    rel->rd_node           = reln;
    for (int i{ 0 }; i < ForkNumber::NUMS_FORKNUM; i++) {
        rel->md_fd[i] = nullptr;
    }

    _data.Put(reln, rel);
    return rel;
}

BlockNumber
Smgr::Nblocks(SMgrRelation reln, ForkNumber forknum) {
    return mdnblocks(reln, forknum);
}

void
Smgr::Create(SMgrRelation reln, ForkNumber forknum) {
    mdcreate(reln, forknum);
}

void
Smgr::Read(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer) {
    mdread(reln, forknum, blocknum, buffer);
}

void
Smgr::Write(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer) {
    mdwrite(reln, forknum, blocknum, buffer);
}

void
Smgr::Extend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer) {
    mdextend(reln, forknum, blocknum, buffer);
}

void
Smgr::Close(SMgrRelation reln) {
    for (int i{ 0 }; i < INIT_FORKNUM; i++) {
        mdclose(reln, (ForkNumber)i);
    }
    _data.Remove(reln->rd_node);
}

// ------
void
RelationOpenSmgr(Relation rel) {
    if (rel->rd_smgr == nullptr) {
        rel->rd_smgr = smgr->Open(rel->rd_node);
    }
}
