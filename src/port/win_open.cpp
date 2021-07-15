#ifdef _WIN32

#include <windows.h>
#include <io.h>
#include <fcntl.h>

int
win32_open(const char* path) {
    HANDLE hFile;

    hFile = CreateFile(path,                         // name of the write
                       GENERIC_READ | GENERIC_WRITE, // open for writing
                       0,                            // do not share
                       NULL,                         // default security
                       OPEN_ALWAYS,                  // create new file only
                       FILE_ATTRIBUTE_NORMAL,        // normal file
                       NULL);                        // no attr. template

    if (hFile == INVALID_HANDLE_VALUE) {
        return -1;
    }

    int fd = _open_osfhandle((intptr_t)hFile, O_TRUNC);
    return fd;
}

#endif