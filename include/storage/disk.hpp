#ifndef _disk_hpp_
#define _disk_hpp_

#include <fstream>
#include <filesystem>

class disk
{
	std::fstream _file;
	std::filesystem::path _path;
public:
	disk(std::filesystem::path path);
	disk(const disk& disk);
	int nblock();
	int write(char* buf, int block);
	int read(char* buf, int block);
	void close();
	bool open();
	int extend(char* buf, int blocknum);
	bool exist();
	void create();
};

#endif