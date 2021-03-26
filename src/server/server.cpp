#include <iostream>
#include <string>
using namespace std;



class Palloc {
public:
    void* operator new(size_t size)
    {
        cout << "operator new size " << size << " with string " << endl;
        return std::malloc(size);
    }

    void operator delete(void* pointee)
    {
        cout << "operator delete" << endl;
        std::free(pointee);
    }
};

class X : public Palloc
{
public:
    X() { cout << "constructor of X" << endl; }
    ~X() { cout << "destructor of X" << endl; }

    
private:
    int num;

    
};

class Other {
public:
    Other(int i, int j) {
        cout << "constructor of Other" << endl;
        _i = i;
        _j = j;
    }
    ~Other() { cout << "destructor of Other" << endl; }

    int _i,_j;
};

template<typename K, typename... Args>
K* palloc(Args &&...args) {
    void* buf = std::malloc(sizeof(K));
    K* k = new(buf) K(std::forward<Args>(args)...);
    return k;
}

template<typename K>
void pfree(K* ptr) {
    ptr->~K();
    std::free(ptr);
}
class T {
private:
    int i;
    int j;
public:
    T(int _i, int _j) :i{ _i }, j{ _j } {}
};
int main()
{
    T* t = new T{1,2};
    return 0;
}