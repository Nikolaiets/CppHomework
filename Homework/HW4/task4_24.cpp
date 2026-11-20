#include <cctype>
#include <iostream>
#include <string>

std::string remove_zeros_and_fives(const std::string& number_str) {
    std::string result;
    result.reserve(number_str.size());

    for (char ch : number_str) {
        if (ch != '0' && ch != '5') {
            result.push_back(ch);
        }
    }

    return result;
}

bool is_valid_natural_number(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    bool has_non_zero = false;
    for (char ch : str) {
        if (!std::isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
        if (ch != '0') {
            has_non_zero = true;
        }
    }

    return has_non_zero;
}

int main() {
    std::string n;

    std::cout << "Enter a natural number n: ";
    if (!(std::cin >> n) || !is_valid_natural_number(n)) {
        std::cerr << "Error: Please enter a valid natural number (positive integer).\n";
        return 1;
    }

    const std::string filtered = remove_zeros_and_fives(n);

    if (filtered.empty()) {
        std::cout << "Result: no remaining digits (all digits were 0 or 5).\n";
    } else {
        std::cout << "Result: " << filtered << '\n';
    }

    return 0;
}