#include "storage/disk.hpp"
#include "storage/page.hpp"

disk::disk(std::filesystem::path path) :_path{ path } {

}

int
disk::nblock() {
	open();
	std::streampos begin, end;
	_file.seekg(std::ios::beg);
	begin = _file.tellg();
	_file.seekg(0, std::ios::end);
	end = _file.tellg();
	auto sz = end - begin;
	close();
	return sz / BLKSZ;
}

int
disk::write(char* page, int block) {
	open();
	int off = BLKSZ * block;
	_file.seekp(off, std::ios::beg);
	_file.write(page, BLKSZ);
	_file.flush();
	close();
	return 0;
}

int
disk::read(char* page, int block) {
	open();
	int off = BLKSZ * block;
	_file.seekg(off, std::ios::beg);
	_file.read(page, BLKSZ);
	close();
	return 0;
}

void
disk::close() {
	_file.close();
}

bool
disk::open() {
	if (!_file.is_open()) {
		_file.open(_path, std::ios::in | std::ios::out | std::ios::binary);
	}
	return _file.is_open();
}

int
disk::extend(char* buf, int blocknum) {
	open();
	int off = BLKSZ * blocknum;
	_file.seekp(off, std::ios::beg);
	_file.write(buf, BLKSZ);
	_file.flush();
	close();
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