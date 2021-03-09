#include "storage/disk.hpp"
#include "storage/page.hpp"

disk::disk(std::filesystem::path path) :_path{ path } {

}

int
disk::nblock() {
	std::streampos begin, end;
	_file.seekg(std::ios::beg);
	begin = _file.tellg();
	_file.seekg(0, std::ios::end);
	end = _file.tellg();
	auto sz = end - begin;
	return sz / BLKSZ;
}

int
disk::write(char* page, int block) {
	int off = BLKSZ * block;
	_file.seekp(off, std::ios::beg);
	_file.write(page, BLKSZ);
	_file.flush();
	return 0;
}

int
disk::read(char* page, int block) {
	int off = BLKSZ * block;
	_file.seekg(off, std::ios::beg);
	_file.read(page, BLKSZ);
	return 0;
}

void
disk::close() {
	_file.close();
}

bool
disk::open() {
	_file.open(_path, std::ios::in | std::ios::out | std::ios::binary);
	return _file.is_open();
}

int
disk::extend(char* buf, int blocknum) {
	int off = BLKSZ * blocknum;
	_file.seekp(off, std::ios::beg);
	_file.write(buf, BLKSZ);
	return 0;
}

void
disk::create() {
	_file.open(_path, std::ios::out);
	_file.close();
}

bool
disk::exist() {
	return std::filesystem::exists(_path);
}