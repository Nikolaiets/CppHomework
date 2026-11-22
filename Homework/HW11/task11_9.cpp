#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool create_sample_file_f(const std::string& filename_f) {
    std::ofstream out(filename_f);
    if (!out) {
        return false;
    }

    out << "10 25 -4 -12 7 -8 3 -1\n";
    return true;
}

bool read_integers_from_file(const std::string& filename, std::vector<int>& values) {
    std::ifstream in(filename);
    if (!in) {
        return false;
    }

    values.clear();
    int x = 0;
    while (in >> x) {
        values.push_back(x);
    }
    return true;
}

void write_vector_to_file(const std::string& filename, const std::vector<int>& values) {
    std::ofstream out(filename);
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            out << ' ';
        }
        out << values[i];
    }
    out << '\n';
}

void process_file_f_to_g_alternating(const std::string& file_f,
                                     const std::string& file_h,
                                     const std::string& file_g) {
    std::vector<int> f_values;
    if (!read_integers_from_file(file_f, f_values)) {
        std::cerr << "Error: Could not open file '" << file_f << "' for reading.\n";
        return;
    }

    int pos_count = 0;
    int neg_count = 0;
    for (int x : f_values) {
        if (x > 0) {
            ++pos_count;
        } else if (x < 0) {
            ++neg_count;
        }
    }

    if (pos_count != neg_count) {
        std::cout << "File '" << file_f << "' does not contain an equal number of positive ("
                  << pos_count << ") and negative (" << neg_count << ") numbers. Nothing done.\n";
        return;
    }

    {
        std::ofstream h_out(file_h);
        if (!h_out) {
            std::cerr << "Error: Could not open auxiliary file '" << file_h << "' for writing.\n";
            return;
        }
        for (int x : f_values) {
            if (x > 0) {
                h_out << x << ' ';
            }
        }
        for (int x : f_values) {
            if (x < 0) {
                h_out << x << ' ';
            }
        }
    }

    std::vector<int> pos_list;
    std::vector<int> neg_list;
    {
        std::ifstream h_in(file_h);
        if (!h_in) {
            std::cerr << "Error: Could not open auxiliary file '" << file_h << "' for reading.\n";
            return;
        }
        int x = 0;
        while (h_in >> x) {
            if (x > 0) {
                pos_list.push_back(x);
            } else if (x < 0) {
                neg_list.push_back(x);
            }
        }
    }
    std::vector<int> g_values;
    g_values.reserve(pos_list.size() + neg_list.size());
    for (std::size_t i = 0; i < pos_list.size(); ++i) {
        g_values.push_back(pos_list[i]);
        g_values.push_back(neg_list[i]);
    }

    std::ofstream g_out(file_g);
    if (!g_out) {
        std::cerr << "Error: Could not open output file '" << file_g << "' for writing.\n";
        return;
    }

    for (std::size_t i = 0; i < g_values.size(); ++i) {
        if (i > 0) {
            g_out << ' ';
        }
        g_out << g_values[i];
    }
    g_out << '\n';

    std::cout << "Successfully wrote alternating-sign sequence to '" << file_g
              << "' using auxiliary file '" << file_h << "'.\n";
}

int main() {
    const std::string file_f = "F.txt";
    const std::string file_h = "H.txt";
    const std::string file_g = "G.txt";

    int choice = 0;
    std::cout << "Choose option (1 - create sample F.txt, 2 - enter custom integers into F.txt): ";
    if (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cerr << "Error: Invalid option.\n";
        return 1;
    }

    if (choice == 1) {
        if (!create_sample_file_f(file_f)) {
            std::cerr << "Error: Could not create '" << file_f << "'.\n";
            return 1;
        }
        std::cout << "Sample file '" << file_f << "' created.\n";
    } else {
        int n = 0;
        std::cout << "Enter number of integers in F: ";
        if (!(std::cin >> n) || n < 0) {
            std::cerr << "Error: Count must be non-negative.\n";
            return 1;
        }

        std::vector<int> custom(static_cast<std::size_t>(n));
        std::cout << "Enter " << n << " integers: ";
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> custom[static_cast<std::size_t>(i)])) {
                std::cerr << "Error: Invalid integer.\n";
                return 1;
            }
        }
        write_vector_to_file(file_f, custom);
    }

    process_file_f_to_g_alternating(file_f, file_h, file_g);

    std::vector<int> result_g;
    if (read_integers_from_file(file_g, result_g) && !result_g.empty()) {
        std::cout << "Contents of " << file_g << ": ";
        for (std::size_t i = 0; i < result_g.size(); ++i) {
            if (i > 0) {
                std::cout << ' ';
            }
            std::cout << result_g[i];
        }
        std::cout << '\n';
    }

    return 0;
}