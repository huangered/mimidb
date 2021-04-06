#include "storage/fd.hpp"
#include "port/port.hpp"

int
PathNameOpenFile(const char* filename) {
	return open(filename);
}
