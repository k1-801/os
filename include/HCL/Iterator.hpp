#pragma once

#ifndef HCL_ITERATOR_HPP
#define HCL_ITERATOR_HPP

namespace Hcl
{
    template<class Container, Data>
    class Iterator
    {
        private:
            Container* container;
            Data*      data;

        public:
            Iterator<Container, Data> operator ++ (); // Next
            Iterator<Container, Data> operator -- ();
            Data&                     operator *  ();
    };
}

#endif // HCL_ITERATOR_HPP