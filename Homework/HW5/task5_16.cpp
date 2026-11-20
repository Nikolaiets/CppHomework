#include <cmath>
#include <iomanip>
#include <iostream>

long double compute_sum_i(long double x, long double eps) {
    long double sum = 0.0L;
    long double term = 1.0L;

    for (int k = 1; std::fabsl(term) >= eps; ++k) {
        sum += term;
        term *= (-x) * (static_cast<long double>(k + 2) / static_cast<long double>(k));
    }

    return sum;
}

int main() {
    long double x = 0.0L;
    long double eps = 0.0L;

    std::cout << "Enter x (|x| < 1): ";
    if (!(std::cin >> x) || std::fabsl(x) >= 1.0L) {
        std::cerr << "Error: x must satisfy |x| < 1.\n";
        return 1;
    }

    std::cout << "Enter epsilon (> 0): ";
    if (!(std::cin >> eps) || eps <= 0.0L) {
        std::cerr << "Error: epsilon must be greater than 0.\n";
        return 1;
    }

    const long double approx_sum = compute_sum_i(x, eps);
    const long double exact_y = 1.0L / std::powl(1.0L + x, 3.0L);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Approximate sum: " << approx_sum << '\n';
    std::cout << "Exact value:    " << exact_y << '\n';

    return 0;
}
