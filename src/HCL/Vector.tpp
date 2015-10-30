#include "../../include/Allocator.hpp"

namespace Hcl
{
    template <class T>
    Vector<T>::Vector(uint64_t n)
    {
        data = new VectorData<T>(n);
    }
    template <class T>
    Vector<T>::Vector(uint64_t n, const T& e)
    {
        data = new VectorData<T>(n, e);
    }
    template <class T>
    Vector<T>::Vector(VectorData<T>* d)
    {
        data = d;
        ++(d->refs);
    }
    
    template <class T>
    void Vector<T>::pushBack(const T& e)
    {
        if(data->refs > 1)
        {
            --(data->refs);
            data = allocator->copy(data);
            data->refs = 1;
        }
        if(data->_endall == data->_end)
        {
            data->realloc(data->size() * 2);
        }
        *(data->_end) = e;
        ++(data->_end);
    }
    
    template <class T>
    void Vector<T>::popBack()
    {
        if(data->size() > 1)
        {
            data->_end->~T();
            --data->_end;
        }
    }
}