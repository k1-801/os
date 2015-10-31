#include "../include/Window.hpp"

Window::Window(const char* _t, uint64_t _x, uint64_t _y, uint64_t _h, uint64_t _w)
{
    title  = _t;
    x      = _x;
    y      = _y;
    height = _h;
    width  = _w;
}