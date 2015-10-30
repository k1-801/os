#pragma once

#ifndef HCL_EXCEPTION_HPP
#define HCL_EXCEPTION_HPP

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
