#include "../../include/Allocator.hpp"

namespace Hcl
{
    template <class T>
    Vector<T>::Vector()
    {
        data = 0;
    }
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
    void Vector<T>::_cow()
    {
        if(!data)
        {
            data = (VectorData<T>*)(allocator->allocate(sizeof(VectorData<T>)));
            data->clear();
            data->refs = 1;
        }
        if(data->refs > 1)
        {
            --(data->refs);
            data = (VectorData<T>*)(allocator->copy(data, sizeof(VectorData<T>)));
            data->refs = 1;
        };
    }
    
    template <class T>
    uint64_t Vector<T>::getSize() const
    {
        return (data ? data->getSize() : 0);
    }
    
    template <class T>
    void Vector<T>::pushBack(const T& e)
    {
        _cow();
        data->pushBack(e);
    }
    
    template <class T>
    void Vector<T>::popBack()
    {
        _cow();
        data->popBack();
    }
    
    template <class T>
    T& Vector<T>::first()
    {
        return data->first(); 
    }
    template <class T>
    T& Vector<T>::last()
    {
        return data->last();
    }
    template <class T>
    T& Vector<T>::at(uint64_t n)
    {
        return data->at(n);
    }
    template <class T>
    T& Vector<T>::operator [] (uint64_t n)
    {
        return data->at(n);
    }
}