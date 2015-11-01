#include "../../include/Allocator.hpp"

#include "../../include/Syslog.hpp"

namespace Hcl
{
    template <class T>
    VectorData<T>::VectorData()
    {
        clear();
        refs = 0;
    }
    
    template <class T>
    uint64_t VectorData<T>::getSize() const
    {
        log("[VectorData] getSize");
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
    void VectorData<T>::realloc(uint64_t n)
    {
        log("[VectorData] realloc");
        if(n > _end - _begin)
        {
            allocator->reallocate(_begin, n * sizeof(T));
        }
        _end = _begin + n;
        _endall = _end;
    }
    
    template <class T>
    void VectorData<T>::resize(uint64_t n)
    {
        log("[VectorData]: resize");
        uint64_t c = _end - _begin, i;
        if(c == n)
            return;
        if(c < n)
        {
            realloc(n);
            //for(i = c; i < n; ++i)
                //_begin[i].T();
        }
        else
            for(i = c; i >= n; --i)
                _begin[i].~T();
        _end = _begin + n;
    }
    
    template <class T>
    void VectorData<T>::pushBack(const T& e)
    {
        log("[VectorData]: pushBack");
        resize((_end - _begin) * 2);
        //if(_end == _endall)
        //    realloc((_end - _begin) * 2);
        /// Have to choose one
        *(_end) = e;
        //_end->T(e);
        ++_end;
    }
    
    template <class T>
    void VectorData<T>::clear()
    {
        log("[VectorData] clear");
        _begin = 0;
        _end = 0;
        _endall = 0;
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