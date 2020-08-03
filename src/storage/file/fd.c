#include "storage/fd.h"
#include "port/disk.h"
#include "util/mctx.h"
#include "storage/page.h"

void file_init(const char* path) {
    mcreate(path);
}

fd* file_open(const char* path) {
    fd* f = palloc(sizeof(fd));
    f->filePtr = mopen(path);
    return f;
}


void file_read(fd* fd, int blocknum, char* buf) {
    int offset1 = blocknum * BLKSZ;
    mread(fd->filePtr, buf, BLKSZ, offset1);
}

void file_write(fd* fd, int blocknum, char* buf) {
    int offset1 = blocknum * BLKSZ;
    mwrite(fd->filePtr, buf, BLKSZ, offset1);
}

void file_close(fd* fd) {
    mclose(fd->filePtr);
    pfree(fd);
}
