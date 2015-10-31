#pragma once

#ifndef HCL_STD_HPP
#define HCL_STD_HPP

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

// C
#include <stdint.h>

#define HCL_CONCAT(a,b) a##b
#define HCL_QUOTATE(a) #a

namespace Hcl
{
    template <class T>
    const T& Min(const T& a, const T& b)
    {
        return (a < b ? a : b);
    }
    
    template <class T>
    const T& Min(const T& a, const T& b, const T& c)
    {
        return ((a <= b && a <= c) ? a : ((b <= a && b <= c) ? b : c));
    }

    template <class T>
    const T& Max(const T& a, const T& b)
    {
        return (a > b ? a : b);
    }
    
    template <class T>
    const T& Max(const T& a, const T& b, const T& c)
    {
        return ((a >= b && a >= c) ? a : ((b >= a && b >= c) ? b : c));
    }

    template <class T>
    T Abs(const T& a)
    {
        return (a < 0 ? -a : a);
    }
    
    template <class T>
    void swap(T& a, T& b)
    {
        T c;
        c = a;
        a = b;
        b = c;
    }
    
    template <class T>
    void MakeHeap(T* a, T* n)
    {
        uint64_t i, c;
        for(i = n - a; i > 0;)
        {
            --i;
            if(a[i] < a[i / 2])
                Swap(a[i], a[i / 2]);
        }
    }
    
    template <class T>
    void _FixHeap(T* a, T* n)
    {
        uint64_t i;
        for(i = (n - a) + !((n - a) % 2); i > 0;)
        {
            i -= 2;
            if(a[i] < a[i / 2])
                Swap(a[i], a[i / 2]);
        }
    }
    
    template <class T>
    void Sort(T* a, T* n)
    {
        MakeHeap(a, n);
        T* i;
        for(i = a; i < n; ++i)
        {
            _FixHeap(i, n);
        }
    }
}

#endif // HCL_STD_HPP
