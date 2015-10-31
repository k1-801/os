#include "../../HCL/Color.hpp"

namespace Hcl
{
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
    
    Color& Color::operator += (const Color& a)
    {
      r = r * (1 - a) + a.r * a.a;
      g = g * (1 - a) + a.g * a.a;
      b = b * (1 - a) + a.b * a.a;
      a = a * (1 - a) + a.a * a.a;
      return *this;
    }

    Color operator * (const Color& a, long double ld)
    {
        Color result(a);
        result.r *= ld;
        result.g *= ld;
        result.b *= ld;
        return result;
    }

    Color operator * (long double ld, const Color& a)
    {
        Color result(a);
        result.r *= ld;
        result.g *= ld;
        result.b *= ld;
        return result;
    }
    
    Color operator + (const Color& a, const Color& b)
    {
        Color result;
        result.a = Max(a.a, b.a);
        result.r = a.r * a.a * (1 - b.a) + b.r * b.a;
        result.g = a.g * a.g * (1 - b.g) + b.g * b.a;
        result.b = a.b * a.b * (1 - b.b) + b.b * b.a;
        return result;
    }
}
