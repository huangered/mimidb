#include "port/disk.hpp"
#include <sys/stat.h>

void
DiskFile::open(const char* path) {
    if (_f != nullptr) {
        close();
    }
    auto i = fopen_s(&_f, path, "rb+");
    if (i != 0) {
        i = fopen_s(&_f, path, "wb+");
    }
}


bool
DiskFile::read(char* buf, Size size, Size offset) {
    fseek(_f, offset, SEEK_SET);
    fread(buf, sizeof(char), size, _f);
    return true;
}

bool
DiskFile::write(char* buf, Size size, Size offset) {
    fseek(_f, offset, SEEK_SET);
    fwrite(buf, sizeof(char), size, _f);
    return true;
}

void
DiskFile::close() {
    fclose(_f);
}
 
bool
DiskFile::exist(const char* path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
};

int
DiskFile::size() {
    fseek(_f, 0, SEEK_END);
    int sz = ftell(_f);
    return sz;
}