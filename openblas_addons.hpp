#ifndef __KATO_FUNCTION_OPENBLAS_HPP__
#define __KATO_FUNCTION_OPENBLAS_HPP__

#pragma once
#include <vector>
#include <cassert>
#include <openblas/cblas.h>

namespace kato::function
{
    template <typename T>
    void fit(const std::vector<T> &_x, const std::vector<T> &_y, double &_slope, double &_intercept)
    {
        assert(_x.size() == _y.size());
        int n = _x.size();

        double sum_x = 0.0, sum_y = 0.0, sum_xx = 0.0, sum_xy = 0.0;

        for (int i = 0; i < n; ++i)
        {
            double x = static_cast<double>(_x[i]);
            double y = static_cast<double>(_y[i]);

            sum_x += x;
            sum_y += y;
            sum_xx += x * x;
            sum_xy += x * y;
        }

        double denom = n * sum_xx - sum_x * sum_x;
        assert(denom != 0.0); // Prevent divide-by-zero

        _slope = (n * sum_xy - sum_x * sum_y) / denom;
        _intercept = (sum_y - _slope * sum_x) / n;
    }

} // namespace function

// sudo dnf install openblas-devel
// pkg-config --cflags --libs openblas

#endif //__KATO_FUNCTION_OPENBLAS_HPP__