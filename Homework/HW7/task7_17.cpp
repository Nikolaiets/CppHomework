#include <algorithm>
#include <iomanip>
#include <iostream>

int main() {
    long long n = 0;

    std::cout << "Enter natural number n (n > 2): ";
    if (!(std::cin >> n) || n <= 2) {
        std::cerr << "Error: n must be greater than 2 so scores remain after removing max and min.\n";
        return 1;
    }

    long double score = 0.0L;
    if (!(std::cin >> score)) {
        std::cerr << "Error: Invalid score input.\n";
        return 1;
    }

    long double sum = score;
    long double min_score = score;
    long double max_score = score;

    std::cout << "Enter remaining " << (n - 1) << " judge scores:\n";
    for (long long i = 2; i <= n; ++i) {
        if (!(std::cin >> score)) {
            std::cerr << "Error: Invalid score input.\n";
            return 1;
        }

        sum += score;
        min_score = std::min(min_score, score);
        max_score = std::max(max_score, score);
    }

    const long double remaining_sum = sum - min_score - max_score;
    const long double final_score = remaining_sum / static_cast<long double>(n - 2);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Final score: " << final_score << '\n';

    return 0;
}