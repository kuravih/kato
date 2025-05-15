#ifndef __KATO_FUNCTION_CCFITS_ADDONS_H__
#define __KATO_FUNCTION_CCFITS_ADDONS_H__

#pragma once

#include <string>
#include <CCfits/CCfits>

namespace kato::function
{
    const std::string CCfitsTypeToString(const int);
};

// pkg-config --cflags --libs CCfits

#endif // __KATO_FUNCTION_CCFITS_ADDONS_H__