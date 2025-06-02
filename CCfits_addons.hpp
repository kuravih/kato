#ifndef __KATO_FUNCTION_CCFITS_ADDONS_HPP__
#define __KATO_FUNCTION_CCFITS_ADDONS_HPP__

#pragma once

#include <string>
#include <CCfits/CCfits>

namespace kato::function
{
    inline const std::string CCfitsTypeToString(const int _type)
    {
        if (_type == BYTE_IMG)
            return "BYTE_IMG";
        else if (_type == USHORT_IMG)
            return "USHORT_IMG";
        else if (_type == ULONG_IMG) // unsupported by opencv
            return "ULONG_IMG";
        else if (_type == ULONGLONG_IMG) // unsupported by opencv
            return "ULONGLONG_IMG";
        else if (_type == FLOAT_IMG)
            return "FLOAT_IMG";
        else if (_type == DOUBLE_IMG)
            return "DOUBLE_IMG";
        else if (_type == SBYTE_IMG)
            return "SBYTE_IMG";
        else if (_type == SHORT_IMG)
            return "SHORT_IMG";
        else if (_type == LONG_IMG)
            return "LONG_IMG";
        else if (_type == LONGLONG_IMG) // unsupported by opencv
            return "LONGLONG_IMG";
        else
            return "USHORT_IMG";
    }
};

// pkg-config --cflags --libs CCfits

#endif // __KATO_FUNCTION_CCFITS_ADDONS_HPP__