#include <cctype>
#include <iostream>
#include <string>

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

std::string normalize_number(const std::string& str) {
    size_t pos = 0;
    while (pos + 1 < str.size() && str[pos] == '0') {
        ++pos;
    }
    return str.substr(pos);
}

int divide_by_small_int(std::string& num, int divisor) {
    int remainder = 0;
    std::string quotient;
    quotient.reserve(num.size());

    for (char ch : num) {
        int current = remainder * 10 + (ch - '0');
        int digit = current / divisor;
        remainder = current % divisor;

        if (!quotient.empty() || digit != 0) {
            quotient.push_back(static_cast<char>('0' + digit));
        }
    }

    num = quotient.empty() ? "0" : quotient;
    return remainder;
}
bool is_power_of(const std::string& natural_str, int base) {
    std::string current = normalize_number(natural_str);
    if (current == "0") {
        return false;
    }
    if (current == "1") {
        return true; // base^0 == 1
    }

    while (current != "1") {
        int rem = divide_by_small_int(current, base);
        if (rem != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int n = 0;

    std::cout << "Enter natural number n (n > 0): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Error: n must be a positive integer.\n";
        return 1;
    }

    std::string* arr = new std::string[n];

    std::cout << "Enter " << n << " natural long numbers:\n";
    for (int i = 0; i < n; ++i) {
        std::string input;
        if (!(std::cin >> input) || !is_valid_natural_number(input)) {
            std::cerr << "Error: Invalid natural number at index " << i << ".\n";
            delete[] arr;
            return 1;
        }
        arr[i] = normalize_number(input);
    }

    int power_of_two_count = 0;
    int power_of_three_count = 0;

    for (int i = 0; i < n; ++i) {
        if (is_power_of(arr[i], 2)) {
            ++power_of_two_count;
        }
        if (is_power_of(arr[i], 3)) {
            ++power_of_three_count;
        }
    }

    std::cout << "\nNumber of powers of 2: " << power_of_two_count << '\n';
    std::cout << "Number of powers of 3: " << power_of_three_count << '\n';

    delete[] arr;
    return 0;
}