#include "storage/fd.hpp"
#include <fcntl.h>
#ifdef __linux__
#include <unistd.h>
#else
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

int
PathNameOpenFile(const char* filename) {
    int fd;
#ifdef __linux__
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
#else
    fd = open(filename, O_CREAT | O_RDWR, S_IREAD | S_IWRITE);
#endif

    return fd;
}

int
FileRead(File fd, char* buf, int amount) {
    int num = read(fd, buf, amount);
    return num;
}

int
FileWrite(File fd, char* buf, int amount) {
    int num = write(fd, buf, amount);
    return num;
}

int
FileSync(File fd) {
#ifdef __linux__
    return fsync(fd);
#else
    return _commit(fd);
#endif
}

off_t
FileSeek(File fd, off_t offset, int whence) {

    lseek(fd, offset, whence);
    return 0;
}

void
FileClose(File fd) {
    close(fd);
    return;
}
