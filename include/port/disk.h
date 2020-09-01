#ifndef _disk_h_
#define _disk_h_

#include "c.h"

void mcreate(const char* path);
FILE* mopen(const char* path);
bool mread(FILE* f, char* buf, Size size, Size offset);
bool mwrite(FILE* f, char* buf, Size size, Size offset);
void mclose(FILE* f);
bool mexist(const char* path);

#endif