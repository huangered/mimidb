#ifndef _fd_h_
#define _fd_h_

#include "c.hpp"
#include "storage/block.hpp"
#include "util/string.hpp"
#include "port/disk.hpp"

typedef struct fd {
    DiskFile filePtr;
} fd;

void file_init(const char* path);
fd* file_open(const char* path);
void file_read(fd* fd, int blocknum, char* buf);
void file_write(fd* fd, int blocknum, char* buf);
void file_close(fd* fd);
bool file_exist(const char* path);
int file_size(fd* fd);

class Fdisk {
    FILE* file;
public:
    explicit Fdisk(yih::String&);
    ~Fdisk();

    void read(BlockNumber blkno, char* buf);
    void write(BlockNumber blkno, char* buf);
    void close();
    size_t size();
};

#endif // !_fd_h_
