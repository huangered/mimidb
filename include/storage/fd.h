#ifndef _fd_h_
#define _fd_h_

#include "c.h"

typedef struct fd {
    FILE* filePtr;
} fd;

void file_init(const char* path);
fd* file_open(const char* path);
void file_read(fd* fd, int blocknum, char* buf);
void file_write(fd* fd, int blocknum, char* buf);
void file_close(fd* fd);

#endif // !_fd_h_
