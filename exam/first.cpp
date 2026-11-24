#include <iostream>
void f() {
    static int calls = 0;
    ++calls;
    std::cout << "f() called times: " << calls << "\n";
}

int main() {
    f(); // 1
    f(); // 2
    f(); // 3
    return 0;
}
