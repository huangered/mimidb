#include "storage/fd.hpp"
#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#endif
#include <cstdio>
int
main(int argc, char* argv[]) {
    int fd = PathNameOpenFile("test.txt");
    const char* data = "12345";
    lseek(fd, 1, SEEK_SET);
    write(fd, data, 5);
    close(fd);
    return 0;
}
