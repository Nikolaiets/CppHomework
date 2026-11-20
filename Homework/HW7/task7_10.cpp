#include <cmath>
#include <iostream>

int main() {
    long long n = 0;

    std::cout << "Enter natural number n: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Error: n must be a natural number (n >= 1).\n";
        return 1;
    }

    const int k = static_cast<int>(std::floor(std::sqrt(static_cast<long double>(n))));
    int even_count = 0;

    std::cout << "Enter " << n << " integers (a_1 ... a_n): ";
    for (long long i = 1; i <= n; ++i) {
        long long a = 0;
        if (!(std::cin >> a)) {
            std::cerr << "Error: Invalid integer input.\n";
            return 1;
        }

        if (i <= k) {
            if (a % 2 == 0) {
                ++even_count;
            }
        }
    }

    std::cout << "k = " << k << '\n';
    std::cout << "Count of even numbers among a_1^2 ... a_k^2: " << even_count << '\n';

    return 0;
}
