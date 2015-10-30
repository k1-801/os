#pragma once

#ifndef HCL_STRINGDATA_HPP
#define HCL_STRINGDATA_HPP

// C
#include <stdint.h>

// HCL
#include "Std.hpp"

namespace Hcl
{
    class StringData;
}

// HCL
#include "Char.hpp"
#include "Vector.hpp"

namespace Hcl
{
    class StringData : public VectorData<Char>
    {
        friend bool operator <  (const StringData&, const StringData&);
        friend bool operator >  (const StringData&, const StringData&);
        friend bool operator <= (const StringData&, const StringData&);
        friend bool operator >= (const StringData&, const StringData&);
    };
}

#endif // HCL_STRINGDATA_HPP
