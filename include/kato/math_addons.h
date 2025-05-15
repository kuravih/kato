#ifndef __KATO_FUNCTION_MATH_H__
#define __KATO_FUNCTION_MATH_H__

#pragma once

#include <vector>

namespace kato::function
{
    template <typename T>
    void fit(const std::vector<T> &, const std::vector<T> &, double &, double &);
};

// pkg-config --cflags --libs openblas

#endif //__KATO_FUNCTION_MATH_H__