#pragma once

#ifndef HCL_CHAR_HPP
#define HCL_CHAR_HPP

// C
#include <stdint.h>
#include <stdarg.h>

namespace Hcl
{
    class Char
    {
        private:
            uint32_t _c;

        public:
            Char(char);
            Char(uint32_t);
            Char(const char*);
            
            uint32_t getCode() const;
            
            // Operators
            operator bool() const;
            operator uint32_t() const;
            friend bool operator == (const Char&, const Char&);
            friend bool operator != (const Char&, const Char&);
            friend bool operator <  (const Char&, const Char&);
            friend bool operator >  (const Char&, const Char&);
            friend bool operator <= (const Char&, const Char&);
            friend bool operator >= (const Char&, const Char&);
    };

    uint32_t u8c(const char*, uint8_t* = 0); // UTF-8 in char* to Hcl::Char
    uint64_t Ustrcpy(Char*, const Char*);
    uint64_t Ustrlen(const Char*);
     int64_t Uatoi(const Char*);

    uint64_t Uvsprintf(Char*, const Char*, va_list);
    uint64_t Uvsprintf(Char*, const char*, va_list);
    uint64_t Usprintf(Char*, const char*, ...);
    uint64_t Usprintf(Char*, const Char*, ...);
}

#endif // HCL_CHAR_HPP