#include <fstream>
#include <iostream>
#include <list>
#include <string>

int main() {
    std::string input_path;
    std::cout << "Enter input file path: ";
    if (!(std::cin >> input_path)) {
        std::cerr << "Error: Invalid file path input.\n";
        return 1;
    }

    std::ifstream in(input_path);
    if (!in.is_open()) {
        std::cerr << "Error: Could not open file '" << input_path << "'.\n";
        return 1;
    }

    std::list<int> c1;
    std::list<int> c2;

    int value = 0;
    bool reading_second_set = false;
    bool delimiter_found = false;

    while (in >> value) {
        if (value < 0) {
            if (!reading_second_set) {
                reading_second_set = true;
                delimiter_found = true;
            }
            continue;
        }

        if (!reading_second_set) {
            c1.push_back(value);
        } else {
            c2.push_back(value);
        }
    }

    if (in.bad()) {
        std::cerr << "Error: Failed while reading from file.\n";
        return 1;
    }

    if (!delimiter_found) {
        std::cerr << "Warning: No negative separator found; second set may be empty.\n";
    }

    c1.sort();
    c2.sort();

    std::cout << "Sorted list C1: ";
    for (int x : c1) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    std::cout << "Sorted list C2: ";
    for (int x : c2) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    std::list<int> merged = c1;
    merged.merge(c2);

    std::cout << "Merged sorted list: ";
    for (int x : merged) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    return 0;
}
