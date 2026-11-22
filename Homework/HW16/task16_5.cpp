#include <iostream>
#include <utility>
#include <vector>

template <typename T>
class Array {
public:
    Array() : size_(0), data_(nullptr) {}

    explicit Array(std::size_t size, const T& default_val = T{})
        : size_(size), data_(size > 0 ? new T[size] : nullptr) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = default_val;
        }
    }

    Array(const Array& other)
        : size_(other.size_), data_(other.size_ > 0 ? new T[other.size_] : nullptr) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Array(Array&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            T* new_data = other.size_ > 0 ? new T[other.size_] : nullptr;
            for (std::size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data_[i];
            }
            delete[] data_;
            data_ = new_data;
            size_ = other.size_;
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~Array() {
        delete[] data_;
    }

    std::size_t size() const noexcept {
        return size_;
    }

    T& operator[](std::size_t index) {
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        return data_[index];
    }

    void quickSort() {
        quickSort(data_, size_);
    }

    static void quickSort(Array& arr) {
        quickSort(arr.data_, arr.size_);
    }

    static void quickSort(T* arr, std::size_t size) {
        if (arr == nullptr || size < 2) {
            return;
        }
        quickSortRange(arr, 0, size - 1);
    }

    void print(std::ostream& os = std::cout) const {
        for (std::size_t i = 0; i < size_; ++i) {
            if (i > 0) {
                os << ' ';
            }
            os << data_[i];
        }
    }

private:
    std::size_t size_;
    T* data_;

    static void quickSortRange(T* arr, std::size_t low, std::size_t high) {
        std::size_t i = low;
        std::size_t j = high;
        const T pivot = arr[low + (high - low) / 2];

        while (i <= j) {
            while (arr[i] < pivot) {
                ++i;
            }
            while (arr[j] > pivot) {
                --j;
            }
            if (i <= j) {
                std::swap(arr[i], arr[j]);
                ++i;
                if (j > 0) {
                    --j;
                } else {
                    break;
                }
            }
        }

        if (low < j && j < high) {
            quickSortRange(arr, low, j);
        }
        if (i < high) {
            quickSortRange(arr, i, high);
        }
    }
};

int main() {
    std::size_t n = 0;
    std::cout << "Enter number of elements: ";
    if (!(std::cin >> n)) {
        std::cerr << "Invalid size input.\n";
        return 1;
    }

    Array<int> arr(n);
    std::cout << "Enter " << n << " elements:\n";
    for (std::size_t i = 0; i < n; ++i) {
        if (!(std::cin >> arr[i])) {
            std::cerr << "Invalid element input.\n";
            return 1;
        }
    }

    arr.quickSort();
    std::cout << "Sorted via member quickSort(): ";
    arr.print();
    std::cout << '\n';

    std::vector<double> raw = {4.5, 1.2, 9.8, 2.3, 7.1};
    Array<double>::quickSort(raw.data(), raw.size());
    std::cout << "Sorted via static quickSort(ptr, size): ";
    for (std::size_t i = 0; i < raw.size(); ++i) {
        if (i > 0) {
            std::cout << ' ';
        }
        std::cout << raw[i];
    }
    std::cout << '\n';

    Array<int> another(4);
    another[0] = 30;
    another[1] = 10;
    another[2] = 40;
    another[3] = 20;
    Array<int>::quickSort(another);
    std::cout << "Sorted via static quickSort(Array&): ";
    another.print();
    std::cout << '\n';

    return 0;
}