#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    constexpr double eps = 1e-9;
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    std::cout << "Enter coefficients a, b, and c: ";
    if (!(std::cin >> a >> b >> c)) {
        std::cerr << "Error: Invalid input.\n";
        return 1;
    }

    std::cout << std::fixed << std::setprecision(6);

    if (std::fabs(a) < eps) {

        if (std::fabs(b) < eps) {
            if (std::fabs(c) < eps) {
                std::cout << "Number of solutions: infinitely many\n";
            } else {
                std::cout << "Number of solutions: 0\n";
            }
        } else {
            const double x = -c / b;
            std::cout << "Number of solutions: 1\n";
            std::cout << "x = " << x << '\n';
        }
        return 0;
    }

    const double discriminant = b * b - 4.0 * a * c;

    if (discriminant > eps) {
        const double sqrt_d = std::sqrt(discriminant);
        const double x1 = (-b - sqrt_d) / (2.0 * a);
        const double x2 = (-b + sqrt_d) / (2.0 * a);
        std::cout << "Number of solutions: 2\n";
        std::cout << "x1 = " << x1 << '\n';
        std::cout << "x2 = " << x2 << '\n';
    } else if (std::fabs(discriminant) <= eps) {
        const double x = -b / (2.0 * a);
        std::cout << "Number of solutions: 1\n";
        std::cout << "x = " << x << '\n';
    } else {
        std::cout << "Number of solutions: 0 (no real solutions)\n";
    }

    return 0;
}