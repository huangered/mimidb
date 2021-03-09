#include "storage/fd.hpp"
#include "port/disk.hpp"
#include "util/mctx.hpp"
#include "storage/page.hpp"

void file_init(const char* path) {
   
}   

fd* file_open(const char* path) {
    fd* f = new fd();
    f->filePtr.open(path);
    return f;
}

void file_read(fd* fd, int blocknum, char* buf) {
    int offset = blocknum * BLKSZ;
    fd->filePtr.read(buf, BLKSZ, offset);
}

void file_write(fd* fd, int blocknum, char* buf) {
    int offset = blocknum * BLKSZ;
    fd->filePtr.write(buf, BLKSZ, offset);
}

void file_close(fd* fd) {
    fd->filePtr.close();
    delete fd;
}

bool file_exist(const char* path) {
    DiskFile df;
    return df.exist(path);
}

int file_size(fd* fd) {
    return fd->filePtr.size();
}
