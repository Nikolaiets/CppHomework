#include <iomanip>
#include <iostream>

long double compute_sum_a(int n) {
    long double sum = 0.0L;
    long double two_pow_k = 2.0L;

    long double a_prev2 = 0.0L;
    long double a_prev1 = 1.0L;

    for (int k = 1; k <= n; ++k) {
        long double a_k = 0.0L;
        if (k == 1) {
            a_k = a_prev2;
        } else if (k == 2) {
            a_k = a_prev1;
        } else {
            a_k = a_prev1 + static_cast<long double>(k) * a_prev2;
            a_prev2 = a_prev1;
            a_prev1 = a_k;
        }

        sum += two_pow_k * a_k;
        two_pow_k *= 2.0L;
    }

    return sum;
}

long double compute_sum_b(int n) {
    long double sum = 0.0L;
    long double three_pow_k = 3.0L; // 3^1 at k = 1

    long double a_prev2 = 1.0L; // a_1 = 1
    long double a_prev1 = 1.0L; // a_2 = 1

    for (int k = 1; k <= n; ++k) {
        long double a_k = 0.0L;
        if (k == 1) {
            a_k = a_prev2;
        } else if (k == 2) {
            a_k = a_prev1;
        } else {
            a_k = (a_prev1 / static_cast<long double>(k)) + a_prev2;
            a_prev2 = a_prev1;
            a_prev1 = a_k;
        }

        sum += three_pow_k / a_k;
        three_pow_k *= 3.0L;
    }

    return sum;
}

int main() {
    int n = 0;

    std::cout << "Enter positive integer n: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Error: n must be a positive integer.\n";
        return 1;
    }

    const long double sum_a = compute_sum_a(n);
    const long double sum_b = compute_sum_b(n);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Sum (a): " << sum_a << '\n';
    std::cout << "Sum (b): " << sum_b << '\n';

    return 0;
}