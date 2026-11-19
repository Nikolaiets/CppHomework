#include <cmath>
#include <iomanip>
#include <iostream>

double gauss(double x) {
    return std::exp(-(x * x));
}

double gauss_derivative(double x) {
    return -2.0 * x * gauss(x);
}

int main() {
    double x = 0.0;

    std::cout << "Enter x: ";
    if (!(std::cin >> x)) {
        std::cerr << "Error: Invalid input for x.\n";
        return 1;
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "gauss(" << x << ") = " << gauss(x) << '\n';
    std::cout << "gauss_derivative(" << x << ") = " << gauss_derivative(x) << '\n';

    return 0;
}
