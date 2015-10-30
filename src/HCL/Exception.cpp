#include "../../include/HCL/Exception.hpp"

namespace Hcl
{
    Exception::Exception(String s)
    {
        _c = s;
    }
    String Exception::what()
    {
        return _c;
    }
}