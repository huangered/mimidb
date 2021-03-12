#include "storage/smgr.hpp"
#include "access/rel.hpp"
#include "access/relpath.hpp"
#include "storage/disk.hpp"
#include "util/hashmap.hpp"

namespace fs = std::filesystem;

class smgr {
private:
    HashMap<Oid, disk*> _data;
    HashMap<Oid, SMgrRelation> _data2;
public:
    ~smgr();
    bool exists(Oid oid, ForkNumber fork);
    SMgrRelation open(Oid oid, RelFileNode reln, ForkNumber fork);
    BlockNumber nblocks(Oid oid);
    void create(Oid oid, ForkNumber fork);
    void read(Oid oid, ForkNumber fork, char* buf, BlockNumber blkno);
    void write(Oid oid, ForkNumber fork, char* buf, BlockNumber blkno);
    void extend(Oid oid, ForkNumber fork, char* buf);
};

smgr::~smgr() {
    auto values = _data.Values();
    for (auto v : values) {
        delete v;
    }
}

bool
smgr::exists(Oid oid, ForkNumber fork) {
    disk* disk;
    _data.Get(oid, &disk);
    return disk->exist();
}

SMgrRelation
smgr::open(Oid oid, RelFileNode reln, ForkNumber fork) {
    SMgrRelation rel;
    if (_data2.Get(oid, &rel))
        return rel;

    fs::path path = GetRelPath2(reln.dbNode, reln.relNode, fork);
    disk* dfile = new disk{ path };
    if (!dfile->exist()) {
        dfile->create();
    }
    dfile->open();
    _data.Put(oid, dfile);

    rel = new SMgrRelationData;
    rel->smgr_target_nblocks = INVALID_BLOCK;
    rel->smgr_fsm_nblocks = INVALID_BLOCK;

    _data2.Put(oid, rel);

    return rel;
}

BlockNumber
smgr::nblocks(Oid oid) {
    disk* disk;
    _data.Get(oid, &disk);

    return disk->nblock();
}

void
smgr::create(Oid oid, ForkNumber fork) {
    disk* disk;
    _data.Get(oid, &disk);
    disk->create();
}

void
smgr::read(Oid oid, ForkNumber fork, char* buf, BlockNumber blkno) {
    disk* disk;
    _data.Get(oid, &disk);
    disk->read(buf, blkno);
}
void
smgr::write(Oid oid, ForkNumber fork, char* buf, BlockNumber blkno) {
    disk* disk;
    _data.Get(oid, &disk);
    disk->write(buf, blkno);
}
void
smgr::extend(Oid oid, ForkNumber fork, char* buf) {
    disk* disk;
    _data.Get(oid, &disk);
    disk->extend(buf, disk->nblock());
}

smgr _smgr{};

SMgrRelation smgropen(Relation rel, ForkNumber number) {
    return _smgr.open(rel->rd_id, rel->rd_node, number);
}

bool smgrexists(Relation rel, ForkNumber number) {
    return _smgr.exists(rel->rd_id, number);    
}

void
smgrcreate(Relation rel, ForkNumber number) {
    _smgr.create(rel->rd_id, number);
}


BlockNumber smgrblocks(Relation rel, ForkNumber number) {
    _smgr.open(rel->rd_id, rel->rd_node, number);
    return _smgr.nblocks(rel->rd_id);

}

void smgrextend(Relation rel, Page page, BlockNumber blkno, ForkNumber number) {
    _smgr.extend(rel->rd_id, number, page);
}

/*
将buf写到物理盘上
*/
void
smgrwrite(Relation rel, ForkNumber number, BlockNumber blkno, char* buf) {
    _smgr.write(rel->rd_id, number, buf, blkno);
}

void
smgrread(Relation rel, ForkNumber number, BlockNumber blkno, char* buf) {
    _smgr.read(rel->rd_id, number, buf, blkno);
}


// ------
void RelationOpenSmgr(Relation rel, SMgrRelation reln) {
    if (rel->rd_smgr == nullptr) {
        rel->rd_smgr = smgropen(rel, MAIN_FORKNUM);
 }
}
