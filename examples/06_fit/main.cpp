#include "kato/log.h"
#include "kato/function.h"
#include "kato/math_addons.h"
#include <cassert>

// A simple comparison with tolerance
bool approx_equal(double a, double b, double tol = 1e-6) {
    return std::fabs(a - b) < tol;
}

int main() {
    // Known linear relationship: y = 2x + 3
    std::vector<unsigned int> x_vals = {1, 2, 3, 4, 5};
    std::vector<unsigned int> y_vals = {5, 7, 9, 11, 13};

    double slope = 0.0;
    double intercept = 0.0;

    kato::function::fit(x_vals, y_vals, slope, intercept);

    std::cout << "Fitted slope: " << slope << "\n";
    std::cout << "Fitted intercept: " << intercept << "\n";

    assert(approx_equal(slope, 2.0));
    assert(approx_equal(intercept, 3.0));

    std::cout << "Test passed!\n";

    return 0;
}
