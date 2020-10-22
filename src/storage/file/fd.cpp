#include "storage/fd.hpp"
#include "port/disk.hpp"
#include "util/mctx.hpp"
#include "storage/page.hpp"

void file_init(const char* path) {
    mcreate(path);
}   

fd* file_open(const char* path) {
    fd* f = (fd*)palloc(sizeof(fd));
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

bool file_exist(const char* path) {
    return mexist(path);
}

int file_size(fd* fd) {
    int size;
    fseek(fd->filePtr, 0, SEEK_END);
    size = ftell(fd->filePtr);
    return size;
}
