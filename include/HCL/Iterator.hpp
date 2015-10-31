#pragma once

#ifndef HCL_ITERATOR_HPP
#define HCL_ITERATOR_HPP

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

// NOT IMPLEMENTED

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