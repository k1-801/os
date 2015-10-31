#pragma once

#ifndef HCL_SURFACE_HPP
#define HCL_SURFACE_HPP

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

// HCL
#include "Color.hpp"
#include "Std.hpp"
#include "SurfaceData.hpp"

namespace Hcl
{
    class Surface
    {
        public:
            SurfaceData* data;

            uint64_t getWidth () const;
            uint64_t getHeight() const;

            void lockData();
            void lockSize();
            
            void resize(uint64_t, uint64_t);
            void apply(const Surface&, uint64_t, uint64_t);

            // use as surf[x][y];
            SurfaceRow& operator[](uint64_t);
    };
}

#endif // HCL_BITMAP_HPP