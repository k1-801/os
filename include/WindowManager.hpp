#pragma once

#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include "HCL/Std.hpp"
#include "HCL/Vector.hpp"
#include "Window.hpp"
/*
class WindowManager
{
    private:
        Hcl::Vector<Window*>; // Set to Hcl::List

    public:
        init();
        addWindow(Window*);
        delWindow(Window*);
        
}*/

void drawObj(Window*, uint32_t, );
void delWin(Window*);

#endif // WINDOWMANAGER_HPP