#include "storage/smgr.hpp"
#include "access/rel.hpp"
#include "access/relpath.hpp"
#include "storage/disk.hpp"
#include "util/hashmap.hpp"

namespace fs = std::filesystem;

class smgr {
private:
    HashMap<RelFileNode, SMgrRelation> _data;
public:
    ~smgr();
    bool exists(RelFileNode rnode);
    SMgrRelation open(RelFileNode rnode);
    BlockNumber nblocks(RelFileNode rnode, ForkNumber forkNum);
    void create(RelFileNode rnode, ForkNumber fork);
    void read(RelFileNode rnode, ForkNumber fork, char* buf, BlockNumber blkno);
    void write(RelFileNode rnode, ForkNumber fork, char* buf, BlockNumber blkno);
    void extend(RelFileNode rnode, ForkNumber fork, char* buf, BlockNumber blkno);
};

smgr::~smgr() {
    auto values = _data.Values();
    for (auto v : values) {
        delete v;
    }
}

bool
smgr::exists(RelFileNode rnode) {
    SMgrRelation data;
    bool re = _data.Get(rnode, &data);
    return re;
}

SMgrRelation
smgr::open(RelFileNode reln) {
    SMgrRelation rel;
    if (_data.Get(reln, &rel))
        return rel;

    rel = new SMgrRelationData;
    rel->smgr_target_nblocks = INVALID_BLOCK;
    rel->smgr_fsm_nblocks = INVALID_BLOCK;
    rel->rd_node = reln;
    for (int i{0}; i < INIT_FORKNUM; i++) {
        rel->disks[i] = new disk(GetRelPath2(reln.dbNode, reln.relNode, (ForkNumber)i));
        if (!rel->disks[i]->exist()) {
            rel->disks[i]->create();
        }
    }

    _data.Put(reln, rel);
    return rel;
}

BlockNumber
smgr::nblocks(RelFileNode rnode, ForkNumber forkNum) {
    SMgrRelation rel;
    _data.Get(rnode, &rel);
    return rel->disks[forkNum]->nblock();
}

void
smgr::create(RelFileNode rnode, ForkNumber fork) {
    SMgrRelation rel;
    _data.Get(rnode, &rel);
    rel->disks[fork]->create();
}

void
smgr::read(RelFileNode rnode, ForkNumber fork, char* buf, BlockNumber blkno) {
    SMgrRelation rel;
    _data.Get(rnode, &rel);
    rel->disks[fork]->read(buf, blkno);
}

void
smgr::write(RelFileNode rnode, ForkNumber fork, char* buf, BlockNumber blkno) {
    SMgrRelation rel;
    _data.Get(rnode, &rel);
    rel->disks[fork]->write(buf, blkno);
}

void
smgr::extend(RelFileNode rnode, ForkNumber fork, char* buf, BlockNumber blkno) {
    SMgrRelation rel;
    _data.Get(rnode, &rel);
    rel->disks[fork]->extend(buf, blkno);
}

smgr _smgr{};

SMgrRelation smgropen(Relation rel) {
    return _smgr.open(rel->rd_node);
}

bool smgrexists(Relation rel, ForkNumber number) {
    return _smgr.exists(rel->rd_node);    
}

void
smgrcreate(Relation rel, ForkNumber number) {
    _smgr.create(rel->rd_node, number);
}


BlockNumber smgrblocks(Relation rel, ForkNumber number) {
    _smgr.open(rel->rd_node);
    return _smgr.nblocks(rel->rd_node, number);

}

void smgrextend(Relation rel, Page page, BlockNumber blkno, ForkNumber number) {
    _smgr.extend(rel->rd_node, number, page, blkno);
}

/*
将buf写到物理盘上
*/
void
smgrwrite(Relation rel, ForkNumber number, BlockNumber blkno, char* buf) {
    _smgr.write(rel->rd_node, number, buf, blkno);
}

void
smgrread(Relation rel, ForkNumber number, BlockNumber blkno, char* buf) {
    _smgr.read(rel->rd_node, number, buf, blkno);
}


// ------
void RelationOpenSmgr(Relation rel) {
    if (rel->rd_smgr == nullptr) {
        rel->rd_smgr = smgropen(rel);
 }
}
