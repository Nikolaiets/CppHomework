#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

double** allocate_matrix(int rows, int cols) {
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols];
    }
    return matrix;
}

void free_matrix(double** matrix, int rows) {
    if (matrix == nullptr) {
        return;
    }
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void print_matrix(double* const* matrix, int rows, int cols) {
    if (rows <= 0 || cols <= 0 || matrix == nullptr) {
        std::cout << "[Empty matrix]\n";
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(2) << matrix[i][j];
        }
        std::cout << '\n';
    }
}

void fill_random(double** matrix, int rows, int cols, double min_val, double max_val) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min_val, max_val);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dist(gen);
        }
    }
}

bool fill_from_console(double** matrix, int rows, int cols) {
    std::cout << "Enter " << rows * cols << " real numbers row by row:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                std::cerr << "Error: Invalid numeric input at position (" << i << ", " << j << ").\n";
                return false;
            }
        }
    }
    return true;
}

void find_max_position(double* const* matrix, int rows, int cols, int& max_row, int& max_col) {
    max_row = 0;
    max_col = 0;
    double max_val = matrix[0][0];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] > max_val) {
                max_val = matrix[i][j];
                max_row = i;
                max_col = j;
            }
        }
    }
}

double** remove_row_and_col(double* const* src, int rows, int cols, int del_row, int del_col,
                              int& out_rows, int& out_cols) {
    out_rows = rows - 1;
    out_cols = cols - 1;

    if (out_rows <= 0 || out_cols <= 0) {
        out_rows = 0;
        out_cols = 0;
        return nullptr;
    }

    double** dst = allocate_matrix(out_rows, out_cols);
    int r_idx = 0;
    for (int i = 0; i < rows; ++i) {
        if (i == del_row) {
            continue;
        }
        int c_idx = 0;
        for (int j = 0; j < cols; ++j) {
            if (j == del_col) {
                continue;
            }
            dst[r_idx][c_idx] = src[i][j];
            ++c_idx;
        }
        ++r_idx;
    }
    return dst;
}

int main() {
    int n = 0;
    int m = 0;

    std::cout << "Enter number of rows N (N > 0): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Error: N must be a positive integer.\n";
        return 1;
    }

    std::cout << "Enter number of columns M (M > 0): ";
    if (!(std::cin >> m) || m <= 0) {
        std::cerr << "Error: M must be a positive integer.\n";
        return 1;
    }

    int mode = 0;
    std::cout << "Choose input mode (1 - random numbers, 2 - console input): ";
    if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        std::cerr << "Error: Invalid mode selection.\n";
        return 1;
    }

    double** matrix = allocate_matrix(n, m);

    if (mode == 1) {
        double min_val = 0.0;
        double max_val = 0.0;
        std::cout << "Enter minimum and maximum values for random generation: ";
        if (!(std::cin >> min_val >> max_val)) {
            std::cerr << "Error: Invalid range values.\n";
            free_matrix(matrix, n);
            return 1;
        }
        if (min_val > max_val) {
            std::cout << "Note: min > max, swapping bounds.\n";
            double tmp = min_val;
            min_val = max_val;
            max_val = tmp;
        }
        fill_random(matrix, n, m, min_val, max_val);
    } else {
        if (!fill_from_console(matrix, n, m)) {
            free_matrix(matrix, n);
            return 1;
        }
    }

    std::cout << "\nOriginal matrix (" << n << "x" << m << "):\n";
    print_matrix(matrix, n, m);

    int max_row = 0;
    int max_col = 0;
    find_max_position(matrix, n, m, max_row, max_col);

    std::cout << "\nLargest element is " << std::fixed << std::setprecision(2)
              << matrix[max_row][max_col] << " at row " << max_row << ", col " << max_col
              << " (0-based indexing).\n";

    int new_rows = 0;
    int new_cols = 0;
    double** updated = remove_row_and_col(matrix, n, m, max_row, max_col, new_rows, new_cols);

    std::cout << "\nResulting matrix after deleting row " << max_row << " and col " << max_col << ":\n";
    print_matrix(updated, new_rows, new_cols);

    free_matrix(updated, new_rows);
    free_matrix(matrix, n);

    return 0;
}