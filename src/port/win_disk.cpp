#include "port/disk.hpp"

#include <sys/stat.h>

void mcreate(const char* path) {
    FILE* f = fopen(path, "rb+");
    fclose(f);
}

FILE* mopen(const char* path) {
    FILE* f;
    auto i =  fopen_s(&f, path, "rb+");
    if (i != 0) {
      i=  fopen_s(&f, path, "wb+");
    }
    return f;
}

bool mread(FILE* f, char* buf, Size size, Size offset) {
    fseek(f, offset, SEEK_SET);
    fread(buf, sizeof(char), size, f);
    return false;
}

bool mwrite(FILE* f, char* buf, Size size, Size offset) {
    fseek(f, offset, SEEK_SET);
    fwrite(buf, sizeof(char), size, f);
    return false;
}

void mclose(FILE* f) {
    fclose(f);
}

bool mexist(const char* path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}