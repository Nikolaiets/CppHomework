#include <fstream>
#include <iostream>
#include <string>

std::string digit_to_english(char ch) {
    switch (ch) {
        case '0': return "zero";
        case '1': return "one";
        case '2': return "two";
        case '3': return "three";
        case '4': return "four";
        case '5': return "five";
        case '6': return "six";
        case '7': return "seven";
        case '8': return "eight";
        case '9': return "nine";
        default:  return std::string(1, ch);
    }
}

bool replace_digits_in_file(const std::string& input_path, const std::string& output_path) {
    std::ifstream in_file(input_path, std::ios::in);
    if (!in_file.is_open()) {
        std::cerr << "Error: Could not open input file \"" << input_path << "\".\n";
        return false;
    }

    std::ofstream out_file(output_path, std::ios::out | std::ios::trunc);
    if (!out_file.is_open()) {
        std::cerr << "Error: Could not open output file \"" << output_path << "\".\n";
        return false;
    }

    char ch = '\0';
    while (in_file.get(ch)) {
        if (ch >= '0' && ch <= '9') {
            out_file << digit_to_english(ch);
        } else {
            out_file.put(ch);
        }
    }

    if (in_file.bad()) {
        std::cerr << "Error: Read error occurred while processing \"" << input_path << "\".\n";
        return false;
    }

    return true;
}

int main() {
    std::string input_path;
    std::string output_path;

    std::cout << "Enter input file path: ";
    if (!std::getline(std::cin, input_path) || input_path.empty()) {
        std::cerr << "Error: Input file path cannot be empty.\n";
        return 1;
    }

    std::cout << "Enter output file path: ";
    if (!std::getline(std::cin, output_path) || output_path.empty()) {
        std::cerr << "Error: Output file path cannot be empty.\n";
        return 1;
    }

    if (!replace_digits_in_file(input_path, output_path)) {
        return 1;
    }

    std::cout << "Done. All digits were replaced with their English names in \""
              << output_path << "\".\n";

    return 0;
}