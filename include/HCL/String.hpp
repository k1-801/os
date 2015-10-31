#pragma once

#ifndef HCL_STRING_HPP
#define HCL_STRING_HPP

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

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
