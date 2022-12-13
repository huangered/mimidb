#include "port/shmem.h"

#ifdef __linux__

#include <sys/types.h>
#include <sys/shm.h>

static int key = 1234;

void*
shmem_init(Size BUF_SIZE) {
    int code = shmget(key, BUF_SIZE, IPC_CREAT);
}

void
shmem_close() {
}

#endif