#include <iostream>

int main(int argc, char* argv[])
{
    int* a = new int[10]{0,1,2,3,4,5,6,7,8,9};
    for (int i{}; i < 10; i++) {
        std::cout << *(a + i) << std::endl;
    }
    return 0;
}
