#include "../include/Allocator.hpp"

Allocator* allocator;
extern uint64_t kend;

Allocator::Allocator()
{
    uint64_t t = (uint64_t)(&kend);
    _kernelEnd = (void*)(t);
    //_buildMap();
    _last = (void*)(t - (t % 0x100000) + 0x100000);
}

void* Allocator::allocate(uint64_t size)
{
    _last = (char*)(_last) + 0x1000;
    return _last;
}

void* Allocator::reallocate(void* n, uint64_t s)
{
    if(n)
        return n;
    else
        return allocate(s);
}

void* Allocator::copy(void* o, uint64_t size)
{
    char* n = (char*)(allocate(size));
    uint64_t i;
    for(i = 0; i < size; ++i)
    {
        n[i] = ((char*)(o))[i];
    }
    return n;
}