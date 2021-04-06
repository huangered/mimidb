#include "port/port.hpp"

int main(int argc, char* argv[])
{
  int fd = open("a.js", O_CREAT |O_RDWR , S_IRUSR|S_IWUSR);
    
    return 0;
}
