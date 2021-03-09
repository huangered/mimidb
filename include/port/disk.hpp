#ifndef _diskfile_hpp_
#define _diskfile_hpp_

#include "c.hpp"

class DiskFile {
private:
	FILE* _f;
public:
	void open(const char* path);
	bool read(char* buf, Size size, Size offset);
	bool write(char* buf, Size size, Size offset);
	void close();
	bool exist(const char* path);
	int size();
};

#endif