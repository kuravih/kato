#include "kato/CCfits_addons.h"
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
const std::string kato::function::CCfitsTypeToString(const int _type)
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
// --------------------------------------------------------------------------------------------------------------------