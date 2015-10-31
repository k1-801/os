#pragma once

#ifndef HCL_SURFACEDATA_HPP
#define HCL_SURFACEDATA_HPP

/**
 * This file is a part of Haont Common Library for SmidgenOS
 * It shold be distributed freely with all the rest of the library source code
 *
 * @project HCL
 * @author k1-801 (Kychanov Dmitry)
 */

#include "Color.hpp"
#include "Std.hpp"

typedef Vector<Color> SurfaceRow;

namespace Hcl
{
    class SurfaceData
    {
        private:
            Vector <Vector <Color> > _c;

        public:
            uint64_t refs;

            uint64_t getHeight();
            uint64_t getWidth();
            
            ;
    }
}

#endif // HCL_SURFACEDATA_HPP