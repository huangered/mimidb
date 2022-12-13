#include "storage/fd.h"
#include "storage/smgr.h"

typedef struct _MdFdVec {
    File fd;
} MdFdVec;

static MdFdVec* mdopen(SMgrRelation reln, ForkNumber forknum);

bool
mdexist(SMgrRelation reln, ForkNumber forknum) {
    // close first
    mdclose(reln, forknum);
    MdFdVec* md = mdopen(reln, forknum);
    return md != nullptr;
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

    reln->md_fd[forknum]     = new MdFdVec{};
    reln->md_fd[forknum]->fd = fd;
}

void
mdread(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
    MdFdVec* md = mdopen(reln, forknum);

    FileSeek(md->fd, blocknum * BLKSZ, SEEK_SET);

    FileRead(md->fd, buf, BLKSZ);
}

void
mdwrite(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
    MdFdVec* md = mdopen(reln, forknum);

    FileSeek(md->fd, blocknum * BLKSZ, SEEK_SET);

    FileWrite(md->fd, buf, BLKSZ);

    FileSync(md->fd);
}

BlockNumber
mdnblocks(SMgrRelation reln, ForkNumber forknum) {
    MdFdVec* md = mdopen(reln, forknum);
    int sz      = FileSeek(md->fd, 0, SEEK_END);
    return sz / BLKSZ;
}

void
mdextend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
    MdFdVec* md = mdopen(reln, forknum);
    int off     = BLKSZ * blocknum;
    FileSeek(md->fd, off, SEEK_SET);
    FileWrite(md->fd, buf, BLKSZ);
}

void
mdclose(SMgrRelation reln, ForkNumber forknum) {
    MdFdVec* md = reln->md_fd[forknum];
    if (md == nullptr) {
        return;
    }
    FileClose(md->fd);
    delete md;
    reln->md_fd[forknum] = nullptr;
}

// private method
static MdFdVec*
mdopen(SMgrRelation reln, ForkNumber forknum) {
    MdFdVec* md;
    char* path;
    File fd;

    if (reln->md_fd[forknum] != nullptr) {
        return reln->md_fd[forknum];
    }

    path = GetRelPath(reln->rd_node.dbNode, reln->rd_node.relNode, forknum);

    fd = PathNameOpenFile(path);

    delete[] path;

    reln->md_fd[forknum] = md = new MdFdVec{};
    md->fd                    = fd;

    return md;
}
