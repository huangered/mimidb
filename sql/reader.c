#include "reader.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* data = NULL;

void
reader(const char* file) {
    FILE* f = fopen(file, "r");
    fseek(f, 0L, SEEK_END);
    long sz    = ftell(f);
    fseek(f, 0L, SEEK_SET);
    printf("file size: %ld\n", sz);
    data = malloc(sz);
    assert(data);
    memset(data, 0, sz);

    size_t size = fread(data, sizeof(char), sz, f);

    printf("%zu:%s", size, data);

    fclose(f);
}