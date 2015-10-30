#include "../include/Allocator.hpp"

Allocator __stdAllocator;

Allocator::Allocator()
{
    _buildMap();
}

void* Allocator::Allocate(uint64_t size)
{
    ;
}