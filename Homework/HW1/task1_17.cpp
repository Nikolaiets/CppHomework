#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double x;

    std::cout << "Enter a real number from 0 to 10000: ";
    if (!(std::cin >> x)) {
        std::cerr << "Error: Invalid input.\n";
        return 1;
    }

    if (x < 0.0 || x > 10000.0) {
        std::cerr << "Error: The number must be between 0 and 10000.\n";
        return 1;
    }

    long double result = std::pow(static_cast<long double>(x), 8);

    std::cout << "Result: "
              << std::setw(25) << std::fixed << std::setprecision(4) << result << '\n';

    return 0;
}
