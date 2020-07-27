#ifndef _disk_h_
#define _disk_h_

#include "c.h"

char* disk_read(const char* path);
bool disk_write(const char* path, char* page);

#endif // !_disk_h_
