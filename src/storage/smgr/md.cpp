#include "storage/fd.hpp"
#include "storage/smgr.hpp"

typedef struct _md_vec {
    File fd;
} MdVec;

static MdVec* mdopen(SMgrRelation reln, ForkNumber forknum);

void
mdcreate(SMgrRelation reln, ForkNumber forknum) {
}

void
mdread(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
  MdVec* md = mdopen(reln, forknum);

  FileSeek(md->fd, blocknum*BLKSZ, SEEK_SET);

  FileRead(md->fd, buf, BLKSZ);
}

void
mdwrite(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
  MdVec* md = mdopen(reln, forknum);

  FileSeek(md->fd, blocknum*BLKSZ, SEEK_SET);

  FileWrite(md->fd, buf, BLKSZ);
}

BlockNumber
mdnblocks(SMgrRelation reln, ForkNumber forknum) {
    return 0;
}

void
mdextend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
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
