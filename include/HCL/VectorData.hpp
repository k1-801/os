#pragma once

#ifndef HCL_VECTORDATA_HPP
#define HCL_VECTORDATA_HPP

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

// HCL
#include "Std.hpp"

namespace Hcl
{
    template<class T>
    class VectorData
    {
        //private:
        public:
            T* _begin;
            T* _end;
            T* _endall;

        public:
            uint64_t refs;

            VectorData();
            uint64_t getSize() const;
            uint64_t getAlloc() const;
            bool isEmpty() const;

            void realloc(uint64_t);
            void resize (uint64_t);

            void pushBack(const T&);
            void popBack();

            void erase(uint64_t);
            void erase(uint64_t, uint64_t);
            void fit();
            void clear();

            T&   first();
            T&   last ();
            T&   at          (uint64_t);
            T&   operator [] (uint64_t);
            bool operator == (const VectorData<T>&) const;
            bool operator != (const VectorData<T>&) const;
    };
}

#include "../../src/HCL/VectorData.tpp"

#endif // HCL_VECTORDATA_HPP