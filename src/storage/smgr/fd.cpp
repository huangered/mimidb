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
    fd = open(filename, O_CREAT | O_RDWR , S_IREAD | S_IWRITE);
#endif

    return fd;
}
