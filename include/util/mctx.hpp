#ifndef _memctx_hpp_
#define _memctx_hpp_

#include "c.hpp"

void* palloc(Size size);
void* palloc0(Size size);

void pfree(void* ptr);

class Mctx {
public:
    void* operator new(size_t size)
    {
        void* p = std::malloc(size);

        return p;
    }
    void operator delete(void* p)
    {
        std::free(p);
    }
};


#endif
