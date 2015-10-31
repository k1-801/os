#include "../include/Allocator.hpp"

Allocator* allocator;

Allocator::Allocator()
{
    _kernelEnd = kend;
    //_buildMap();
    _last = _kernelEnd - (_kernelEnd % 0x100000) + 0x100000;
}

void* Allocator::Allocate(uint64_t size)
{
    _last += 0x1000;
    return ;
}