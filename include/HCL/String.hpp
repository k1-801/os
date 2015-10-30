#pragma once

#ifndef HCL_STRING_HPP
#define HCL_STRING_HPP

// C
#include <stdint.h>

namespace Hcl
{
    class String;
}

// HCL
#include "Char.hpp"
#include "Std.hpp"
#include "Vector.hpp"

namespace Hcl
{
    class String : public Vector<Char>
    {
        bool operator <  (const String&) const;
        bool operator >  (const String&) const;
        bool operator <= (const String&) const;
        bool operator >= (const String&) const;
    };
}

#endif // HCL_STRING_HPP
