#include "storage/fd.hpp"
#include "port/port.hpp"

int
PathNameOpenFile(const char* filename) {
  return open(filename, O_CREAT |O_RDWR , S_IRUSR|S_IWUSR);
}
