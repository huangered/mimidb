#include "storage/fd.hpp"
#include "port/port.hpp"

int
PathNameOpenFile(const char* filename) {
  return open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR|S_IWUSR);
}
