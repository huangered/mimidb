#include "storage/smgr.hpp"
#include "storage/page.hpp"
#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include "storage/fd.hpp"

int
Md::Nblock(SMgrRelation reln, ForkNumber forknum) {
	int fd = reln->fd[forknum];

	if (fd <= 0) {
		fd = Open(reln, forknum);
	}

	int sz = lseek(fd, 0, SEEK_END);

	return sz / BLKSZ;
}

int
Md::Write(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
	int fd = reln->fd[forknum];

	if (fd <= 0) {
		fd = Open(reln, forknum);
	}

	int off = BLKSZ * blocknum;
	
	lseek(fd, off, SEEK_SET);
	int sz = write(fd, buf, BLKSZ);
	return sz;
}

int
Md::Read(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
	int fd = reln->fd[forknum];

	if (fd <= 0) {
		fd = Open(reln, forknum);
	}

	int off = BLKSZ * blocknum;
	lseek(fd, off, SEEK_SET);
	read(fd, buf, BLKSZ);
	return 0;
}

void
Md::Close(SMgrRelation reln, ForkNumber forknum) {
	int fd = reln->fd[forknum];
	if (fd > 0) {
		close(fd);
		reln->fd[forknum] = 0;
	}
}

int
Md::Open(SMgrRelation reln, ForkNumber forknum) {
	int fd = reln->fd[forknum];
	if (fd <= 0) {
		char* path = GetRelPath(reln->rd_node.dbNode, reln->rd_node.relNode, forknum);

		int fd2 = PathNameOpenFile(path);
		reln->fd[forknum] = fd2;
		fd = fd2;
	}
	return fd;
}

int
Md::Extend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum, char* buf) {
	int fd = reln->fd[forknum];

	if (fd <= 0) {
		fd = Open(reln, forknum);
	}
	int off = BLKSZ * blocknum;
	lseek(fd, off, SEEK_SET);
	int sz = write(fd, buf, BLKSZ);
	return sz;
}

void
Md::Create(SMgrRelation reln, ForkNumber forknum) {
	Open(reln, forknum);
}

bool
Md::Exist(SMgrRelation reln, ForkNumber forknum) {
	char* path = GetRelPath(reln->rd_node.dbNode, reln->rd_node.relNode, forknum);
	bool existed = (access(path, 0) == 0);
	delete[] path;
	return existed;
}

void
Md::Remove(SMgrRelation reln, ForkNumber forknum) {
	Close(reln, forknum);
	char* path = GetRelPath(reln->rd_node.dbNode, reln->rd_node.relNode, forknum);
	remove(path);
	delete[] path;
}