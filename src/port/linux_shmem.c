#include "port/shmem.h"

#ifdef __linux__

void* shmem_init(Size BUF_SIZE) {
    return NULL;
}

void shmem_close() {

}

#endif