#include "debug.hpp"
#include <stdio.h>

void
log(const char* msg) {
#ifdef _log_
    fprintf(stdout, "info: %s\n", msg);
#endif
}

void
logErr(const char* msg) {
    fprintf(stderr, "err: %s\n", msg);
}