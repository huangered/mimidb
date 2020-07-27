#ifndef _SH_MEM_H_
#define _SH_MEM_H_

#include "c.h"

void* shmem_init(Size size);
void shmem_close();

#endif // !_SH_MEM_H_
