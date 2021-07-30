#include "storage/smgr.hpp"
#include "access/rel.hpp"
#include "access/relpath.hpp"
#include "util/hashmap.hpp"
#include "port/port.hpp"

Smgr* smgr = new Smgr{};

Smgr::Smgr() {
    md = new Md{};
}

Smgr::~Smgr() {
    auto values = _data.Values();
    for (auto v : values) {
        delete v;
    }
    delete md;
}

bool
Smgr::Exists(SMgrRelation reln, ForkNumber forknum) {
    return md->Exist(reln, forknum);
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
    for (int i{ 0 }; i < INIT_FORKNUM; i++) {
        rel->fd[i] = 0;
    }

    _data.Put(reln, rel);
    return rel;
}

BlockNumber
Smgr::Nblocks(SMgrRelation reln, ForkNumber forknum) {
    return md->Nblock(reln, forknum);
}

void
Smgr::Create(SMgrRelation reln, ForkNumber forknum) {
    md->Create(reln, forknum);
}

void
Smgr::Read(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer) {
    md->Read(reln, forknum, blocknum, buffer);
}

void
Smgr::Write(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer) {
    md->Write(reln, forknum, blocknum, buffer);
}

void
Smgr::Extend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buffer) {
    md->Extend(reln, forknum, blocknum, buffer);
}

void
Smgr::Close(SMgrRelation reln) {
    for (int i{ 0 }; i < INIT_FORKNUM; i++) {
        md->Close(reln, (ForkNumber)i);
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
