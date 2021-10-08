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
    fd = _open(filename, O_CREAT | O_RDWR, S_IREAD | S_IWRITE);
#else
    fd      = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
#endif

    return fd;
}

int
FileRead(File fd, char* buf, int amount) {
#ifdef _WIN32
    int num = _read(fd, buf, amount);
#else
    int num = read(fd, buf, amount);
#endif
    return num;
}

int
FileWrite(File fd, const char* buf, int amount) {
#ifdef _WIN32
    int num = _write(fd, buf, amount);
#else
    int num = write(fd, buf, amount);
#endif
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
#ifdef _WIN32
    long num = _lseek(fd, offset, whence);
#else
    long num = lseek(fd, offset, whence);
#endif
    return num;
}

void
FileClose(File fd) {
#ifdef _WIN32
    _close(fd);
#else
    close(fd);
#endif
}

void
DirMake(const char* dirname) {
#ifdef _WIN32

#else
    mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
}
