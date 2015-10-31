#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "HCL/Std.hpp"
#include "HCL/String.hpp"

class Window
{
    public:
        uint64_t width;
        uint64_t height;
        uint64_t x;
        uint64_t y;
        /*Hcl::String*/const char* title;

        Window(/*Hcl::String*/ const char*, uint64_t, uint64_t, uint64_t, uint64_t);
};

bool drawObj(Window* target, uint32_t color, uint32_t captColor);
bool drawObj(Window* target,bool noBtmCrn);
void delWin(Window* wnd);

#endif // WINDOW_HPP