#pragma once

#ifndef GOMENU_HPP
#define GOMENU_HPP

// HCL
#include "HCL/String.hpp"
#include "HCL/Vector.hpp"

class GoMenuEntry
{
    public:
        uint64_t uid;
        Hcl::String name;
        int64_t (*callback)(void);
};

class GoMenu
{
    private:
        static Hcl::Vector<GoMenuEntry> _c;

    public:
        static void main();
        static void addEntry(GoMenuEntry&);
};

#endif // GOMENU_HPP