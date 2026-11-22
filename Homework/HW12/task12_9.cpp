#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string file_path;
    std::cout << "Enter file path (e.g. input.txt): ";
    if (!(std::cin >> file_path)) {
        std::cerr << "Error: Invalid file path input.\n";
        return 1;
    }

    std::ifstream in_file(file_path);
    if (!in_file.is_open()) {
        std::cerr << "Error: Could not open file '" << file_path << "' for reading.\n";
        return 1;
    }

    std::vector<unsigned long long> numbers;
    long long temp = 0;

    while (in_file >> temp) {
        if (temp <= 0) {
            std::cerr << "Error: File must contain only natural numbers (> 0).\n";
            return 1;
        }
        numbers.push_back(static_cast<unsigned long long>(temp));
    }

    if (in_file.bad()) {
        std::cerr << "Error: Failed while reading from file.\n";
        return 1;
    }
    in_file.close();

    if (numbers.empty()) {
        std::cout << "File is empty. Nothing to rewrite.\n";
        return 0;
    }
    std::vector<unsigned long long> result = numbers;
    for (size_t i = 0; i + 1 < numbers.size(); ++i) {
        if (numbers[i] > numbers[i + 1]) {
            result[i] = numbers[i] * numbers[i];
        }
    }
    std::ofstream out_file(file_path, std::ios::trunc);
    if (!out_file.is_open()) {
        std::cerr << "Error: Could not open file '" << file_path << "' for writing.\n";
        return 1;
    }

    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) {
            out_file << ' ';
        }
        out_file << result[i];
    }
    out_file << '\n';

    std::cout << "File successfully rewritten.\n";
    return 0;
}