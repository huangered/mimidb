#include <iostream>
using namespace std;

class Mctx {
public:
    void* operator new(size_t size)
    {
        cout << "Overloading new operator with size: " << size << endl;
        void* p = malloc(size);

        return p;
    }
    void operator delete(void* p)
    {
        cout << "Overloading delete operator " << endl;
        free(p);
    }
};

class A : public Mctx {
private:
    int i;
    int j;
    int q[];
public:
    
    void* operator new(size_t size, int num)
    {
        cout << "Overloading new operator with size: " << size << endl;
        size_t q = offsetof(A, q);
        q += sizeof(int) * num;
        void* p = malloc(q);

        return p;
    }

   /* void* operator new(size_t size)
    {
        cout << "Overloading new operator with size: " << size << endl;
        size_t q = offsetof(A, q);
        q += sizeof(int) * 5;
        void* p = malloc(q);

        return p;
    }*/
};

class G :public Mctx {
    int i;
    int j;
    int q[];
    
    void* operator new(size_t size, int num)
    {
        cout << "Overloading new operator with size: " << size << endl;
        size_t q = offsetof(G, q);
        q += sizeof(int) * num;
        void* p = malloc(q);

        return p;
    }
};

template<typename T>
uintptr_t test2(T i) {
    return static_cast<uintptr_t>(i);
}

template<typename T>
T revert2(uintptr_t ptr) {
    return static_cast<T>(ptr);
}

int main(int argc, char* argv[])
{
    int* i = new int{ 10 };
    std::cout <<std::hex<< i << std::endl;
    uintptr_t g2 = reinterpret_cast<uintptr_t>(i);
    std::cout <<std::hex<< g2 << std::endl;
    int* j = reinterpret_cast<int*>(g2);

    int q{ 20 };

    uintptr_t g3 = static_cast<uintptr_t>(q);
    
    int j22 = static_cast<int>(g3);



    return 0;
}
