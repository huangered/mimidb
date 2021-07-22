#ifndef _fd_hpp_
#define _fd_hpp_

#include <sys/types.h>
#include <dirent.h>

typedef int File;

File PathNameOpenFile(const char* filename);
int FileRead(File fd, char* buf, int amount);
int FileWrite(File fd, char* buf, int amount);
int FileSync(File fd);
off_t FileSeek(File fd, off_t offset, int whence);
void FileClose(File fd);

#endif
