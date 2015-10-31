#pragma once

#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

// HCL
#include "Std.hpp"
#include "VectorData.hpp"

namespace Hcl
{
    template<class T>
    class Vector
    {
        public:
            VectorData<T>* data; // Please do not use in your code, it is public for debugging purposes

            Vector(uint64_t);
            Vector(uint64_t, const T&);
            Vector(VectorData<T>*);

            uint64_t getSize() const;
            uint64_t getAlloc() const;

            void realloc(uint64_t);
            void resize(uint64_t);
            void resize(uint64_t, const T&);

            void pushBack(const T&);
            void popBack();

            void erase(uint64_t);
            void erase(uint64_t, uint64_t);
            void clear();
            void fit();
            void swap(Vector<T>&);
            
            bool operator == (const Vector&) const;
            bool operator != (const Vector&) const;
    };
}

#include "../../src/HCL/Vector.tpp"

#endif // VECTOR_HPP_INCLUDED