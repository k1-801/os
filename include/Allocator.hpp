#pragma once

#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

// C
#include <stdint.h>

/**
 * Allocator class acts as a virtual memory manager
 */

typedef uint64_t WrappedPtr;

class Allocator
{
    private:
        void* _kernelStart;
        void* _kernelEnd;
        void* _last;
        //PageTable* pageTable;

    public:
        void*   allocate(uint64_t);        // malloc
        void* reallocate(void*, uint64_t); // realloc
        void*       copy(void*, uint64_t); // memcpy

        // Mapped
        WrappedPtr   allocateMapped(uint64_t, uint64_t);
        WrappedPtr reallocateMapped(WrappedPtr, uint64_t);
        WrappedPtr       copyMapped(WrappedPtr, uint64_t);

        WrappedPtr* wrapMapped(uint64_t, void*);
        void*     unwrapMapped(WrappedPtr);
};

extern Allocator* allocator;

#endif // ALLOCATOR_HPP