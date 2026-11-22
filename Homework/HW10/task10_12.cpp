#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Price {
    long long hryvnias = 0;
    int kopecks = 0;
};
long long to_kopecks(const Price& p) {
    return p.hryvnias * 100LL + p.kopecks;
}

void print_price(const Price& p) {
    std::cout << p.hryvnias << " UAH "
              << std::setw(2) << std::setfill('0') << p.kopecks << " kop."
              << std::setfill(' ');
}
int find_cheapest_index(const std::vector<Price>& items) {
    int best_idx = 0;
    long long min_kop = to_kopecks(items[0]);

    for (size_t i = 1; i < items.size(); ++i) {
        long long cur_kop = to_kopecks(items[i]);
        if (cur_kop < min_kop) {
            min_kop = cur_kop;
            best_idx = static_cast<int>(i);
        }
    }
    return best_idx;
}
int find_most_expensive_index(const std::vector<Price>& items) {
    int best_idx = 0;
    long long max_kop = to_kopecks(items[0]);

    for (size_t i = 1; i < items.size(); ++i) {
        long long cur_kop = to_kopecks(items[i]);
        if (cur_kop > max_kop) {
            max_kop = cur_kop;
            best_idx = static_cast<int>(i);
        }
    }
    return best_idx;
}
std::vector<int> find_within_10_uah_of_average(const std::vector<Price>& items, double& out_avg_kop) {
    long long sum_kop = 0;
    for (const Price& item : items) {
        sum_kop += to_kopecks(item);
    }

    out_avg_kop = static_cast<double>(sum_kop) / static_cast<double>(items.size());
    constexpr double max_diff_kop = 10.0 * 100.0; // 10 hryvnias = 1000 kopecks

    std::vector<int> matches;
    for (size_t i = 0; i < items.size(); ++i) {
        double cur_kop = static_cast<double>(to_kopecks(items[i]));
        if (std::fabs(cur_kop - out_avg_kop) <= max_diff_kop) {
            matches.push_back(static_cast<int>(i));
        }
    }
    return matches;
}

int main() {
    int n = 0;
    std::cout << "Enter number of items N (N > 0): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Error: N must be a positive integer.\n";
        return 1;
    }

    std::vector<Price> items(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        std::cout << "Item #" << (i + 1) << " - enter hryvnias and kopecks (e.g. 25 50): ";
        if (!(std::cin >> items[static_cast<size_t>(i)].hryvnias >> items[static_cast<size_t>(i)].kopecks) ||
            items[static_cast<size_t>(i)].hryvnias < 0 ||
            items[static_cast<size_t>(i)].kopecks < 0 ||
            items[static_cast<size_t>(i)].kopecks >= 100) {
            std::cerr << "Error: Invalid price (hryvnias >= 0, 0 <= kopecks < 100).\n";
            return 1;
        }
    }

    const int cheapest_idx = find_cheapest_index(items);
    const int expensive_idx = find_most_expensive_index(items);

    double avg_kop = 0.0;
    const std::vector<int> near_avg_indices = find_within_10_uah_of_average(items, avg_kop);

    std::cout << "\n--- Search Results ---\n";
    std::cout << "1) Cheapest item (#" << (cheapest_idx + 1) << "): ";
    print_price(items[static_cast<size_t>(cheapest_idx)]);
    std::cout << '\n';

    std::cout << "2) Most expensive item (#" << (expensive_idx + 1) << "): ";
    print_price(items[static_cast<size_t>(expensive_idx)]);
    std::cout << '\n';

    const long long avg_uah_whole = static_cast<long long>(avg_kop) / 100LL;
    const int avg_kop_rem = static_cast<int>(std::llround(avg_kop)) % 100;
    std::cout << "Average item cost: ~" << avg_uah_whole << " UAH "
              << std::setw(2) << std::setfill('0') << std::abs(avg_kop_rem) << " kop.\n";

    std::cout << "3) Items within 10 UAH of average cost:\n";
    if (near_avg_indices.empty()) {
        std::cout << "   None found.\n";
    } else {
        for (int idx : near_avg_indices) {
            std::cout << "   - Item #" << (idx + 1) << ": ";
            print_price(items[static_cast<size_t>(idx)]);
            std::cout << '\n';
        }
    }

    return 0;
}