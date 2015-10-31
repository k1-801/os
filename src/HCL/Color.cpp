#include "../../include/HCL/Color.hpp"

namespace Hcl
{
    Color::Color(){}
    Color::Color(uint32_t i)
    {
        a = (i >> 6) & 0xFF;
        r = (i >> 4) & 0xFF;
        g = (i >> 2) & 0xFF;
        b = (i     ) & 0xFF;
    }
    Color::Color(const Color& c1)
    {
        a = c1.a;
        r = c1.r;
        g = c1.g;
        b = c1.b;
    }
    Color::Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
    {
        a = _a;
        r = _r;
        g = _g;
        b = _b;
    }
    
    Color::operator uint32_t()
    {
        return (a << 6) | (r << 4) | (g << 2) | b;
    }

    Color& Color::operator *= (long double ld)
    {
        r *= ld;
        g *= ld;
        b *= ld;
        return *this;
    }
    
    Color& Color::operator += (const Color& c1)
    {
        r = r * (1 - a) + c1.r * c1.a;
        g = g * (1 - a) + c1.g * c1.a;
        b = b * (1 - a) + c1.b * c1.a;
        a = a * (1 - a) + c1.a * c1.a;
        return *this;
    }

    Color operator * (const Color& c1, long double ld)
    {
        Color result(c1);
        result.r *= ld;
        result.g *= ld;
        result.b *= ld;
        return result;
    }

    Color operator * (long double ld, const Color& c1)
    {
        Color result(c1);
        result.r *= ld;
        result.g *= ld;
        result.b *= ld;
        return result;
    }
    
    Color operator + (const Color& c1, const Color& c2)
    {
        Color result;
        result.r = c1.r * (1 - c2.a) + c2.r * c2.a;
        result.g = c1.g * (1 - c2.a) + c2.g * c2.a;
        result.b = c1.b * (1 - c2.a) + c2.b * c2.a;
        result.a = c1.a * (1 - c2.a) + c2.a * c2.a;
        return result;
    }
}
