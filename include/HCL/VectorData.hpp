#pragma once

#ifndef HCL_VECTORDATA_HPP
#define HCL_VECTORDATA_HPP

// HCL
#include "Std.hpp"

namespace Hcl
{
    template<class T>
    class VectorData
    {
        private:
            T* _begin;
            T* _end;
            T* _endall;
            uint64_t refs;

        public:
            uint64_t getSize() const;
            uint64_t getAlloc() const;
            bool isEmpty() const;

            void realloc();
            void resize();

            void pushBack();
            void popBack();

            void erase(uint64_t);
            void erase(uint64_t, uint64_t);
            void fit();
            void clear();

            T&   at          (uint64_t);
            T&   operator [] (uint64_t);
            bool operator == (const VectorData<T>&) const;
            bool operator != (const VectorData<T>&) const;
    };
}

#endif // HCL_VECTORDATA_HPP