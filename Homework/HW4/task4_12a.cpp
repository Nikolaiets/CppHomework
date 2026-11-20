#include <iomanip>
#include <iostream>

double eval_polynomial(double x, int n) {
    double sum = 1.0;
    double current_power = x;

    for (int k = 0; k <= n; ++k) {
        sum += current_power;
        current_power *= current_power;
    }

    return sum;
}

int main() {
    double x = 0.0;
    int n = 0;

    std::cout << "Enter x: ";
    if (!(std::cin >> x)) {
        std::cerr << "Error: Invalid input for x.\n";
        return 1;
    }

    std::cout << "Enter non-negative integer n: ";
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Error: n must be a non-negative integer.\n";
        return 1;
    }

    const double result = eval_polynomial(x, n);

    std::cout << "y = " << std::fixed << std::setprecision(6) << result << '\n';

    return 0;
}