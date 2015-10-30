#include "../../include/HCL/Char.hpp"

namespace Hcl
{
    Char::Char(char c)
    {
        _c = c;
    }
    Char::Char(uint32_t c)
    {
        _c = c;
    }
    Char::Char(const char* s)
    {
        _c = u8c(s);
    }
    
    uint32_t Char::getCode() const
    {
        return _c;
    }

    // Operators
    Char::operator bool() const
    {
        return _c;
    }
    Char::operator uint32_t() const
    {
        return _c;
    }
    bool operator == (const Char& a, const Char& b){return (a._c == b._c);}
    bool operator != (const Char& a, const Char& b){return (a._c != b._c);}
    bool operator <  (const Char& a, const Char& b){return (a._c <  b._c);}
    bool operator >  (const Char& a, const Char& b){return (a._c >  b._c);}
    bool operator <= (const Char& a, const Char& b){return (a._c <= b._c);}
    bool operator >= (const Char& a, const Char& b){return (a._c >= b._c);}
    
    uint32_t u8c(const char* raw, uint8_t* os)
    {
        uint32_t result;
        uint8_t bytes;
        uint8_t i;
        char c = *raw;

        if(c >> 6 == 2) // Check whether character is corrupted
        {
            if(os)
            {
                *os = 0;
                while(*(raw + (*os)++) >> 6 == 2);
            }
            return -1;
        }

        bytes = 1;
        while((c >> bytes++) & 1 && bytes <= 6);
        result = ((c << bytes) >> bytes);
        for(i = 1; i < bytes; ++i)
        {
            result <<= 6;
            result |= *(raw + i) & 0x3F;
        }
        return result;
    }

    uint64_t Ustrlen(const Char* s)
    {
        uint64_t result = 0;
        if(!s)
            return 0;
        while(*(s + result++));
        return result;
    }
    uint64_t Ustrcpy(Char* a, const Char* b)
    {
        ;
    }
    uint64_t Uvsprintf(Char* to, const char* format, va_list va)
    {
    }
    uint64_t Uvsprintf(Char* to, const Char* format, va_list va)
    {
        uint64_t fn = Ustrlen(format);
        while(*format)
        {
            if(*format == Char('%')) // Optimize this
            {
                uint64_t i;
                bool parsed;
                for(i = 0; i < !parsed; ++i)
                while(!parsed)
                {
                    
                }
            }
            else
            {
                *to = *format;
                ++to;
                ++format;
            }
        }
    }
    uint64_t Uvsprintf(Char* to, const char* format, ...)
    {
        va_list va;
        va_start(va, format);
        Uvsprintf(to, format, va);
        va_end(va);
    }
    uint64_t Uvsprintf(Char* to, const Char* format, ...)
    {
        va_list va;
        va_start(va, format);
        Uvsprintf(to, format, va);
        va_end(va);
    }
}