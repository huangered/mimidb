#include "storage/smgr.hpp"
#include "access/rel.hpp"
#include "access/relpath.hpp"
#include "util/mctx.hpp"
#include "storage/fd.hpp"

bool smgrexists(Relation rel, ForkNumber number) {
    bool result = false;
    char* path = GetRelPath(rel->rnode, number);

    result = file_exist(path);

    pfree(path);
    return result;
}

void
smgrcreate(Relation rel, ForkNumber number) {
    char* path = GetRelPath(rel->rnode, number);
    file_init(path);
    pfree(path);
}


BlockNumber smgrblocks(Relation rel, ForkNumber number) {
    char* path = GetRelPath(rel->rnode, number);

    fd* fd = file_open(path);
    int size = file_size(fd);
    file_close(fd);
    return size / BLKSZ;
}

void smgrextend(Relation rel, Page page, BlockNumber blkno, ForkNumber number) {
    char* path = GetRelPath(rel->rnode, number);

    fd* fd = file_open(path);
    file_write(fd, blkno, page);
    file_close(fd);
    pfree(path);
}

/*
将buf写到物理盘上
*/
void
smgrwrite(Relation rel, ForkNumber number, BlockNumber blkno, char* buf) {
    char* path = GetRelPath(rel->rnode, number);
    fd* fd = file_open(path);
    file_write(fd, blkno, buf);
    file_close(fd);
    pfree(path);
}

void
smgrread(Relation rel, ForkNumber number, BlockNumber blkno, char* buf) {
    char* path = GetRelPath(rel->rnode, number);
    fd* fd = file_open(path);
    file_write(fd, blkno, buf);
    file_close(fd);
    pfree(path);
}
