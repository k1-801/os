#pragma once

#ifndef HCL_EXCEPTION_HPP
#define HCL_EXCEPTION_HPP

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

#include "String.hpp"

namespace Hcl
{
    class Exception
    {
        private:
            String _c;

        public:
            Exception(String);
            String what();
    }
}

#endif // HCL_EXCEPTION_HPP
