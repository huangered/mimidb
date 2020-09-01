#include "port/disk.h"

#include <sys/stat.h>

void mcreate(const char* path) {
    FILE* f = fopen(path, "wb");
    fclose(f);
}

FILE* mopen(const char* path) {
    FILE* f = fopen(path, "rb+");
    if (f == NULL) {
        mcreate(path);
    }
    f = fopen(path, "rb+");
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