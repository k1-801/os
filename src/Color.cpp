#include "../../include/HCL/Color.hpp"

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

namespace Hcl
{
    Color::Color(uint32_t d)
    {
        // *(uint32_t)(&a) = d; 
        a = (d >> 6) & 0xFF;
        r = (d >> 4) & 0xFF;
        g = (d >> 2) & 0xFF;
        b = (d     ) & 0xFF;
    }
    
    Color::Color(uint8_t sr, uint8_t sg, uint8_t sb, uint8_t sa)
    {
        a = sa;
        r = sr;
        g = dg;
        b = sb;
    }
    
    Color::operator uint32_t()
    {
        return (a << 6) | (r << 4) | (g << 3) | b;
    }
    
    Color& Color::operator *= (long double ld)
    {
        r *= ld;
        g *= ld;
        b *= ld;
        return *this;
    }
    
    Color operator * (const Color& c, long double ld)
    {
        Color result(c);
        c.r *= ld;
        c.g *= ld;
        c.b *= ld;
        return result;
    }
    
    Color operator * (long double ld, const Color& c)
    {
        Color result(c);
        c.r *= ld;
        c.g *= ld;
        c.b *= ld;
        return result;
    }
    
    Color operator + (const Color& a, const Color& b)
    {
        Color result;
        result.a = max()
        a.x = a.x
    }
}