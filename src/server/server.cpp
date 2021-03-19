#include <cstdlib>
#include <iostream>


struct A {
    int i;
    uint8_t a[1024];
};
int
main(int argc, char* argv[]) {
    int i = 1;
    int* arr[4];
    arr[0] = &i;

    std::cout << *(arr[0]) << std::endl;
    
    return 0;
}
