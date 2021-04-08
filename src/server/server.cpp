#include <cstdlib>
#include <cstring>
#include <cstdio>

class G {
public:
    G() {}
    ~G(){}
};

template<typename T>
T* palloc0(size_t sz) {
    void* p = std::malloc(sz);
    return reinterpret_cast<T*>(p);
}

void* palloc(size_t sz) {
    void* p = std::malloc(sz);
    return p;
}

void pfree(void* ptr) {
    std::free(ptr);
}

int main(int argc, char* argv[])
{
    int* i = palloc0<int>(10 * sizeof(int));
    int* j = (int*)palloc(10 * sizeof(int));
    pfree(i);
    pfree(j);

    return 0;
}
