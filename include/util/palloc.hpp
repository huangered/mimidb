#ifndef _palloc_hpp_
#define _palloc_hpp_

typedef struct MemoryContextData* MemoryContext;

extern void* MemoryContextAlloc(MemoryContext context, Size size);
extern void* palloc(Size size);
extern void* palloc0(Size size);
extern void pfree(void* ptr);

template <class T, class... Args>
T*
pnew(Args... args) {
    T* p = static_cast<T*>(palloc(sizeof(T)));
    new (p) T{ args... };
    return p;
}

template <class T>
void
pdelete(T* p) {
    p->~T();
    pfree(p);
}

#endif
