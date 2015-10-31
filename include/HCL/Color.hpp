#pragma once

#ifndef HCL_COLOR_HPP
#define HCL_COLOR_HPP

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

#include "Std.hpp"

namespace Hcl
{
    class Color
    {
        public:
            Color();
            Color(uint32_t);
            Color(const Color&);
            Color(uint8_t, uint8_t, uint8_t, uint8_t = 0xFF);
            uint8_t a, r, g, b;
            
            operator uint32_t();
            Color& operator *= (long double);
            Color& operator += (const Color&);
            Color& operator =  (const Color&);
    };

    Color operator *  (const Color&, long double);
    Color operator *  (long double, const Color&);
    Color operator +  (const Color&, const Color&);
}

#endif // HCL_COLOR_HPP
