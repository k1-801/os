#pragma once

#ifndef HCL_VECTORDATA_TPP
#define HCL_VECTORDATA_TPP

namespace Hcl
{
    template <class T>
    uint64_t VectorData<T>::getSize() const
    {
        return _end - _begin;
    }
    
    template <class T>
    uint64_t VectorData<T>::getAlloc() const
    {
        return _endall - _begin;
    }
    
    template <class T>
    bool VectorData<T>::isEmpty() const
    {
        return _end == _begin;
    }
    
    template <class T>
    T& VectorData<T>::first()
    {
        return *_begin;
    }
    
    template <class T>
    T& VectorData<T>::last()
    {
        return *(_end - 1);
    }
    
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
        uint64_t n = _begin -   _end;
        if(n != a._begin - a._end)
            return false;
        for(i = 0; i < n; ++i)
            if(*(_begin + i) != *(a._begin + i))
                return false;
        return true;
    }
    
    template <class T>
    bool VectorData<T>::operator != (const VectorData& a) const
    {
        uint64_t i;
        uint64_t n = _begin -   _end;
        if(n != a._begin - a._end)
            return true;
        for(i = 0; i < n; ++i)
            if(*(_begin + i) != *(a._begin + i))
                return true;
        return false;
    }
}

#endif // HCL_VECTORDATA_TPP