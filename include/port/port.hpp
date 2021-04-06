#ifndef _port_hpp_
#define _port_hpp_

#ifdef _WIN32

  extern int win32_open(const char* path);

  #define open(a) win32_open(a)
#else

  #include <unistd.h>
  #include <sys/stat.h>
  #include <fcntl.h>

#endif



#endif // !_port_hpp_
