#include <cstdlib>
#include <cstring>
#include <cstdio>

int main(int argc, char* argv[])
{
    int i = 1;
    int* value = (int*)std::malloc(2 * sizeof(int));
    memcpy(value, &i, sizeof(int));
    memcpy(value + 1, &i, sizeof(int));
    
    for (int i{}; i < 2; i++) {
        printf("%d\r\n", value[i]);
    }

    return 0;
}
