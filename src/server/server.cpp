#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "storage/disk.hpp"

struct A {
    int i;
    uint8_t a[1024];
};
int
main(int argc, char* argv[]) {
  
    disk disk1{ std::filesystem::path{"1.txt"} };
    disk1.create();
    disk1.open();
    std::cout << disk1.nblock() << std::endl;
    char* buf = new char[1024*8];
    disk1.extend(buf, 0);
    std::cout << disk1.nblock() << std::endl;
    disk1.close();
    return 0;
}
