#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double x;

    std::cout << "Enter an additional number x: ";
    if (!(std::cin >> x)) {
        std::cerr << "Error: invalid input.\n";
        return 1;
    }

    if (x <= 0.0) {
        std::cerr << "Error: the decimal logarithm is defined only for numbers x > 0.\n";
        return 1;
    }

    double result = std::log10(x);

    std::cout << "log10(" << x << ") = "
              << std::fixed << std::setprecision(3) << result << '\n';

    return 0;
}