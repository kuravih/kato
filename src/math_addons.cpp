#include <iostream>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <chrono>
#include <cassert>
#include <cblas.h>

#include "kato/math_addons.h"
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
template <typename T>
void kato::function::fit(const std::vector<T> &_x, const std::vector<T> &_y, double &_slope, double &_intercept)
{

    assert(_x.size() == _y.size());

    int n = _x.size();

    std::vector<double> b(n, 0.0), A(2 * n, 0.0), x(2, 0.0);

    for (int i = 0; i < n; ++i)
    {
        b[n] = static_cast<double>(_y[i]);
        A[i] = static_cast<double>(_x[i]);
        A[i + n] = 1.0;
    }

    _slope = 0.0;
    _intercept = 0.0;

    // Use cblas_dgemv to calculate A^T * A * solution = A^T * b
    cblas_dgemv(CblasRowMajor, CblasTrans, n, 2, 1.0, A.data(), 2, b.data(), 1, 0.0, x.data(), 1);

    _slope = x[0];
    _intercept = x[1];

    return;
}
template void kato::function::fit<uint>(const std::vector<uint> &_x, const std::vector<uint> &_y, double &_slope, double &_intercept);
// --------------------------------------------------------------------------------------------------------------------