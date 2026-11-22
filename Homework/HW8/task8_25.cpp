#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    int n = 0;

    std::cout << "Enter the size n of the square matrix (n x n): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Error: Matrix size must be a positive integer.\n";
        return 1;
    }

    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));

    std::cout << "Enter the elements of the " << n << "x" << n << " matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                std::cerr << "Error: Invalid matrix element.\n";
                return 1;
            }
        }
    }
    bool found_positive = false;
    double min_positive = std::numeric_limits<double>::infinity();
    int min_row = -1;
    int min_col = -1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > 0.0 && (!found_positive || matrix[i][j] < min_positive)) {
                found_positive = true;
                min_positive = matrix[i][j];
                min_row = i;
                min_col = j;
            }
        }
    }

    if (!found_positive) {
        std::cout << "No positive elements found in the matrix. Nothing to swap.\n";
        return 0;
    }

    std::cout << "\nMinimum positive element: " << min_positive
              << " at row " << min_row << ", column " << min_col << " (0-based index).\n";
    for (int k = 0; k < n; ++k) {
        std::swap(matrix[min_row][k], matrix[k][min_col]);
    }

    std::cout << "\nUpdated matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(10) << matrix[i][j];
        }
        std::cout << '\n';
    }

    return 0;
}
