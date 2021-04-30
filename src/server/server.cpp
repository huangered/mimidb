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

int main(int argc, char* argv[])
{
     A* a = new(10) A {};
     cout << sizeof(A) << endl;
     cout << is_pod_v<A> << endl;
     cout << is_pod_v<G> << endl;

    return 0;
}
