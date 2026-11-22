#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Baggage {
    int passenger_id = 0;
    int item_count = 0;
    double total_weight = 0.0;
};

void clear_input_line() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool create_sample_files(const std::string& passengers_file, const std::string& baggage_file) {
    std::ofstream p_out(passengers_file);
    std::ofstream b_out(baggage_file);
    if (!p_out || !b_out) {
        return false;
    }

    p_out << "Ivanenko\n";
    p_out << "Kovalenko\n";
    p_out << "Shevchenko\n";
    p_out << "Bondarenko\n";

    b_out << "1 3 18.5\n";
    b_out << "2 5 24.0\n";
    b_out << "3 5 19.2\n";
    b_out << "4 2 10.0\n";

    return true;
}

bool load_passengers(const std::string& filename, std::vector<std::string>& passengers) {
    std::ifstream in(filename);
    if (!in) {
        return false;
    }

    passengers.clear();
    std::string surname;
    while (std::getline(in, surname)) {
        if (!surname.empty()) {
            passengers.push_back(surname);
        }
    }
    return !passengers.empty();
}

bool load_baggage(const std::string& filename, std::vector<Baggage>& baggage_list) {
    std::ifstream in(filename);
    if (!in) {
        return false;
    }

    baggage_list.clear();
    Baggage b;
    while (in >> b.passenger_id >> b.item_count >> b.total_weight) {
        baggage_list.push_back(b);
    }
    return !baggage_list.empty();
}
void print_max_items_min_weight_passenger(const std::vector<std::string>& passengers,
                                          const std::vector<Baggage>& baggage_list) {
    if (baggage_list.empty()) {
        std::cout << "No baggage records available.\n";
        return;
    }

    int max_items = baggage_list[0].item_count;
    for (const auto& b : baggage_list) {
        if (b.item_count > max_items) {
            max_items = b.item_count;
        }
    }

    bool found_any = false;
    double min_weight_for_max_items = std::numeric_limits<double>::infinity();

    for (const auto& b : baggage_list) {
        if (b.item_count == max_items) {
            if (!found_any || b.total_weight < min_weight_for_max_items) {
                min_weight_for_max_items = b.total_weight;
                found_any = true;
            }
        }
    }

    if (!found_any) {
        std::cout << "No matching passenger found.\n";
        return;
    }

    std::cout << "\n--- Passenger Details (Max Items = " << max_items
              << ", Min Weight for This Count = " << std::fixed << std::setprecision(2)
              << min_weight_for_max_items << ") ---\n";

    for (const auto& b : baggage_list) {
        if (b.item_count == max_items && b.total_weight == min_weight_for_max_items) {
            std::string surname = (b.passenger_id >= 1 &&
                                   static_cast<std::size_t>(b.passenger_id) <= passengers.size())
                                      ? passengers[static_cast<std::size_t>(b.passenger_id) - 1]
                                      : "[Unknown passenger]";

            std::cout << "Passenger ID: " << b.passenger_id
                      << ", Surname: " << surname
                      << ", Items: " << b.item_count
                      << ", Total Weight: " << std::fixed << std::setprecision(2)
                      << b.total_weight << '\n';
        }
    }
}

int main() {
    const std::string passengers_file = "passengers.txt";
    const std::string baggage_file = "baggage.txt";

    int choice = 0;
    std::cout << "Choose option (1 - use/generate sample files, 2 - enter custom data to files): ";
    if (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cerr << "Error: Invalid option.\n";
        return 1;
    }

    if (choice == 1) {
        if (!create_sample_files(passengers_file, baggage_file)) {
            std::cerr << "Error: Could not create sample files.\n";
            return 1;
        }
        std::cout << "Sample files '" << passengers_file << "' and '" << baggage_file
                  << "' created.\n";
    } else {
        int num_passengers = 0;
        std::cout << "Enter number of passengers: ";
        if (!(std::cin >> num_passengers) || num_passengers <= 0) {
            std::cerr << "Error: Number of passengers must be positive.\n";
            return 1;
        }
        clear_input_line();

        std::ofstream p_out(passengers_file);
        if (!p_out) {
            std::cerr << "Error: Could not open " << passengers_file << " for writing.\n";
            return 1;
        }

        for (int i = 1; i <= num_passengers; ++i) {
            std::string surname;
            std::cout << "Enter surname for passenger #" << i << ": ";
            if (!std::getline(std::cin, surname) || surname.empty()) {
                std::cerr << "Error: Invalid surname.\n";
                return 1;
            }
            p_out << surname << '\n';
        }
        p_out.close();

        int num_baggage = 0;
        std::cout << "Enter number of baggage records: ";
        if (!(std::cin >> num_baggage) || num_baggage <= 0) {
            std::cerr << "Error: Number of baggage records must be positive.\n";
            return 1;
        }

        std::ofstream b_out(baggage_file);
        if (!b_out) {
            std::cerr << "Error: Could not open " << baggage_file << " for writing.\n";
            return 1;
        }

        for (int i = 0; i < num_baggage; ++i) {
            Baggage b;
            std::cout << "Enter passenger ID (1.." << num_passengers
                      << "), item count, and total weight: ";
            if (!(std::cin >> b.passenger_id >> b.item_count >> b.total_weight) ||
                b.passenger_id < 1 || b.passenger_id > num_passengers ||
                b.item_count < 0 || b.total_weight < 0.0) {
                std::cerr << "Error: Invalid baggage record.\n";
                return 1;
            }
            b_out << b.passenger_id << ' ' << b.item_count << ' ' << b.total_weight << '\n';
        }
        b_out.close();
    }

    std::vector<std::string> passengers;
    std::vector<Baggage> baggage_list;

    if (!load_passengers(passengers_file, passengers)) {
        std::cerr << "Error: Failed to read passengers file.\n";
        return 1;
    }
    if (!load_baggage(baggage_file, baggage_list)) {
        std::cerr << "Error: Failed to read baggage file.\n";
        return 1;
    }

    print_max_items_min_weight_passenger(passengers, baggage_list);

    return 0;
}