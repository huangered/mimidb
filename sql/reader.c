#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void
reader(const char* file) {
    FILE* f = fopen(file, "r");

    char* buf = malloc(256);
    memset(buf, 0, 256);
    buf[255] = '\0';
    int size = fread(buf, sizeof(char), 255, f);

    printf("%d:%s", size, buf);

    fclose(f);
}