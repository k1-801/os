#pragma once

#ifndef HCL_VECTORDATA_HPP
#define HCL_VECTORDATA_HPP

namespace Hcl
{
    template <class T>
    T& VectorData<T>::at(uint64_t n)
    {
        return *(_begin + n);
    }
    
    template <class T>
    T& VectorData<T>::operator [] (uint64_t n)
    {
        return *(_begin + n);
    }
    
    template <class T>
    bool VectorData<T>::operator == (const VectorData& a) const
    {
        uint64_t i;
        uint64_t n =   _begin -   _end;
        if(n != a._begin - a._end)
            return false;
        for(i = 0; i < n; ++i)
            if(*(_begin + i) != *(a._begin + i))
                return false;
        return true;
    }
}

#endif // HCL_VECTORDATA_HPP