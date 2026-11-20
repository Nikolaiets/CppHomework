#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

constexpr double INF = std::numeric_limits<double>::max();
constexpr double EPS = 1e-12;

double softExponential(double a, double x) {
    if (a < -EPS) {
        const double arg = 1.0 - a * (x + a);
        if (arg <= 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return -std::log(arg) / a;
    }
    if (std::fabs(a) <= EPS) {
        return x;
    }

    if (a * x > 700.0) {
        return INF;
    }
    return (std::exp(a * x) - 1.0) / a + a;
}

double softExponentialDerivative(double a, double x) {
    if (a < -EPS) {
        const double denom = 1.0 - a * (x + a);
        if (denom < 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        if (std::fabs(denom) <= EPS) {
            return INF;
        }
        return 1.0 / denom;
    }
    if (std::fabs(a) <= EPS) {
        return 1.0;
    }

    if (a * x > 709.0) {
        return INF;
    }
    return std::exp(a * x);
}

int main() {
    double a = 0.0;
    double x = 0.0;

    std::cout << "Enter parameters a and x: ";
    if (!(std::cin >> a >> x)) {
        std::cerr << "Error: Invalid input.\n";
        return 1;
    }

    const double val = softExponential(a, x);
    const double deriv = softExponentialDerivative(a, x);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "softExponential(a, x) = " << val << '\n';
    std::cout << "Derivative d/dx softExponential(a, x) = " << deriv << '\n';

    return 0;
}