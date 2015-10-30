#include "../../include/HCL/String.hpp"

namespace Hcl
{
    bool String :: operator <  (const String& a) const
    {
        // Optimization checks
        if((data == a.data) || (data && !a.data))
            return false;
        if((!data || data->isEmpty()) && !a.data->isEmpty())
            return true;

        uint64_t i, n = Min(data->getSize(), a.data->getSize());
        for(i = 0; i < n; ++i)
        {
            if(data->at(i) < a.data->at(i))
                return true;
            if(data->at(i) > a.data->at(i))
                return false;
        }
        return data->getSize() < a.data->getSize();
    }
}