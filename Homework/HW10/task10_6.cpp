#include <cctype>
#include <iostream>
#include <limits>
#include <string>

struct Address {
    std::string city;
    std::string street;
    std::string building;
    int apartment = 0;
};

void clear_input_line() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
bool is_valid_words_only(const std::string& s) {
    bool has_letter = false;
    for (unsigned char ch : s) {
        if (std::isdigit(ch)) {
            return false;
        }
        if (std::isalpha(ch) || ch >= 128) {
            has_letter = true;
        } else if (ch != ' ' && ch != '-') {
            return false;
        }
    }
    return has_letter;
}
bool is_valid_building(const std::string& s) {
    bool has_digit = false;
    for (unsigned char ch : s) {
        if (std::isdigit(ch)) {
            has_digit = true;
        } else if (!std::isalpha(ch) && ch != '/' && ch != '-' && ch != ' ') {
            return false;
        }
    }
    return has_digit;
}

bool read_address(Address& addr) {
    std::cout << "Enter city: ";
    if (!std::getline(std::cin >> std::ws, addr.city) || !is_valid_words_only(addr.city)) {
        std::cerr << "Error: City must contain only words (no digits).\n";
        return false;
    }

    std::cout << "Enter street: ";
    if (!std::getline(std::cin, addr.street) || !is_valid_words_only(addr.street)) {
        std::cerr << "Error: Street must contain only words (no digits).\n";
        return false;
    }

    std::cout << "Enter building: ";
    if (!std::getline(std::cin, addr.building) || !is_valid_building(addr.building)) {
        std::cerr << "Error: Building must contain digits (e.g. 12 or 12A).\n";
        return false;
    }

    std::cout << "Enter apartment number: ";
    if (!(std::cin >> addr.apartment) || addr.apartment <= 0) {
        std::cerr << "Error: Apartment number must be a positive integer.\n";
        clear_input_line();
        return false;
    }

    clear_input_line();
    return true;
}

void print_address(const Address& addr) {
    std::cout << "\n--- Address ---\n"
              << "City:      " << addr.city << '\n'
              << "Street:    " << addr.street << '\n'
              << "Building:  " << addr.building << '\n'
              << "Apartment: " << addr.apartment << '\n';
}

int main() {
    Address addr;

    if (!read_address(addr)) {
        return 1;
    }

    print_address(addr);

    return 0;
}