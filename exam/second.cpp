#include <iostream>
#include <limits>
#include <utility>

long long sum_rec(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sum_rec(n - 1);
}

std::pair<long long, int> f(int n) {
    static int calls = 0;
    ++calls;
    return {sum_rec(n), calls};
}

bool read_int(const char* prompt, int lo, int hi, int& out) {
    while (true) {
        std::cout << prompt;
        int x = 0;
        if (std::cin >> x && x >= lo && x <= hi) {
            out = x;
            return true;
        }
        if (std::cin.eof()) {
            return false;
        }
        std::cout << "Enter an integer from " << lo << " to " << hi << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    int q = 0;
    if (!read_int("q (1..50): ", 1, 50, q)) {
        return 0;
    }

    for (int i = 0; i < q; ++i) {
        int n = 0;
        if (!read_int("n (0..20): ", 0, 20, n)) {
            break;
        }
        auto [sum, calls] = f(n);
        std::cout << "sum = " << sum << ", calls = " << calls << '\n';
    }

    return 0;
}