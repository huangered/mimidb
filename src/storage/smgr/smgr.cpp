#include "storage/smgr.hpp"
#include "access/rel.hpp"
#include "access/relpath.hpp"
#include "storage/disk.hpp"
#include "util/hashmap.hpp"

namespace fs = std::filesystem;

class smgr {
private:
    HashMap<Oid, disk*> _data;
public:
    bool exists(Oid oid, ForkNumber fork);
    void open(Oid oid, ForkNumber fork);
    BlockNumber nblocks(Oid oid);
    void create(Oid oid, ForkNumber fork);
    void read(Oid oid, ForkNumber fork, char* buf, BlockNumber blkno);
    void write(Oid oid, ForkNumber fork, char* buf, BlockNumber blkno);
    void extend(Oid oid, ForkNumber fork, char* buf);
};

bool
smgr::exists(Oid oid, ForkNumber fork) {
    disk* disk;
    _data.Get(oid, &disk);
    return disk->exist();
}

void
smgr::open(Oid oid, ForkNumber fork) {
    if (_data.Exist(oid))
        return;
    fs::path path = GetRelPath2(oid, fork);
    disk* dfile = new disk{ path };
    if (!dfile->exist()) {
        dfile->create();
    }
    dfile->open();
    _data.Put(oid, dfile);
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

void smgropen(Relation rel, ForkNumber number) {
    _smgr.open(rel->oid, number);
}

bool smgrexists(Relation rel, ForkNumber number) {
    return _smgr.exists(rel->oid, number);    
}

void
smgrcreate(Relation rel, ForkNumber number) {
    _smgr.create(rel->oid, number);
}


BlockNumber smgrblocks(Relation rel, ForkNumber number) {
    _smgr.open(rel->oid, number);
    return _smgr.nblocks(rel->oid);

}

void smgrextend(Relation rel, Page page, BlockNumber blkno, ForkNumber number) {
    _smgr.extend(rel->oid, number, page);
}

/*
将buf写到物理盘上
*/
void
smgrwrite(Relation rel, ForkNumber number, BlockNumber blkno, char* buf) {
    _smgr.write(rel->oid, number, buf, blkno);
}

void
smgrread(Relation rel, ForkNumber number, BlockNumber blkno, char* buf) {
    _smgr.read(rel->oid, number, buf, blkno);
}
