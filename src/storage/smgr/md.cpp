#include "storage/fd.hpp"
#include "storage/smgr.hpp"

typedef struct _md_vec {
    File fd;
} MdVec;

static MdVec* mdopen(SMgrRelation reln, ForkNumber forknum);

bool
mdexist(SMgrRelation reln, ForkNumber forknum) {
    return true;
}

void
mdcreate(SMgrRelation reln, ForkNumber forknum) {
    char* path;
    File fd;

    if (reln->md_fd[forknum] != nullptr) {
        return;
    }

    path = GetRelPath(reln->rd_node.dbNode, reln->rd_node.relNode, forknum);
    fd   = PathNameOpenFile(path);

    delete[] path;

    reln->md_fd[forknum]     = new MdVec{};
    reln->md_fd[forknum]->fd = fd;
}

void
mdread(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
    MdVec* md = mdopen(reln, forknum);

    FileSeek(md->fd, blocknum * BLKSZ, SEEK_SET);

    FileRead(md->fd, buf, BLKSZ);
}

void
mdwrite(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
    MdVec* md = mdopen(reln, forknum);

    FileSeek(md->fd, blocknum * BLKSZ, SEEK_SET);

    FileWrite(md->fd, buf, BLKSZ);

    FileSync(md->fd);
}

BlockNumber
mdnblocks(SMgrRelation reln, ForkNumber forknum) {
    MdVec* md = mdopen(reln, forknum);
    int sz    = FileSeek(md->fd, 0, SEEK_END);
    return sz / BLKSZ;
}

void
mdextend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
    MdVec* md = mdopen(reln, forknum);
    int off   = BLKSZ * blocknum;
    FileSeek(md->fd, off, SEEK_SET);
    FileWrite(md->fd, buf, BLKSZ);
}

void
mdclose(SMgrRelation reln, ForkNumber forknum) {
    MdVec* md = mdopen(reln, forknum);
    FileClose(md->fd);
    delete md;
    reln->md_fd[forknum] = nullptr;
}

// private method
static MdVec*
mdopen(SMgrRelation reln, ForkNumber forknum) {
    MdVec* md;
    char* path;
    File fd;

    if (reln->md_fd[forknum] != nullptr) {
        return reln->md_fd[forknum];
    }

    path = GetRelPath(reln->rd_node.dbNode, reln->rd_node.relNode, forknum);

    fd = PathNameOpenFile(path);

    delete[] path;

    reln->md_fd[forknum] = md = new MdVec{};
    md->fd                    = fd;

    return md;
}
