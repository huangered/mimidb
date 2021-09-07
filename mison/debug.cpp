#include "debug.hpp"
#include <stdio.h>

void
log(const char* msg) {
    fprintf(stdout, "info: %s\n", msg);
}

void
logErr(const char* msg) {
    fprintf(stderr, "err: %s\n", msg);
}