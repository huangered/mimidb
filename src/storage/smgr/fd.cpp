#include "storage/fd.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>
#else
#include <unistd.h>
#endif

int
PathNameOpenFile(const char* filename) {
    int fd;
#ifdef _WIN32
    fd = open(filename, O_CREAT | O_RDWR, S_IREAD | S_IWRITE);
#else
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
#endif

    return fd;
}

int
FileRead(File fd, char* buf, int amount) {
    int num = read(fd, buf, amount);
    return num;
}

int
FileWrite(File fd, const char* buf, int amount) {
    int num = write(fd, buf, amount);
    return num;
}

int
FileSync(File fd) {
#ifdef _WIN32
    return _commit(fd);
#else
    return fsync(fd);
#endif
}

off_t
FileSeek(File fd, off_t offset, int whence) {
    long num = lseek(fd, offset, whence);
    return num;
}

void
FileClose(File fd) {
    close(fd);
    return;
}

void
DirMake(const char* dirname) {
  mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}
