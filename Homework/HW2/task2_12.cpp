#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    double radius = 0.0;
    double height = 0.0;

    std::cout << "Enter the base radius of the cone: ";
    if (!(std::cin >> radius)) {
        std::cerr << "Error: Invalid input for radius.\n";
        return 1;
    }

    std::cout << "Enter the height of the cone: ";
    if (!(std::cin >> height)) {
        std::cerr << "Error: Invalid input for height.\n";
        return 1;
    }

    if (radius <= 0.0 || height <= 0.0) {
        std::cerr << "Error: Radius and height must be positive numbers.\n";
        return 1;
    }

    const double pi = std::acos(-1.0);
    const double volume = (1.0 / 3.0) * pi * radius * radius * height;

    std::cout << "Volume of the cone: "
              << std::fixed << std::setprecision(4) << volume << '\n';

    return 0;
}