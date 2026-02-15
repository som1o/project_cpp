/**
 * Program to generate the first n terms of the Fibonacci sequence.
 */

#include <iostream>

int main() {
    int n, first = 0, second = 1, next;

    std::cout << "Enter the number of terms: ";
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Error: Invalid number of terms." << std::endl;
        return 1;
    }

    std::cout << "Fibonacci Sequence: ";
    for (int i = 0; i < n; i++) {
        std::cout << first << (i == n - 1 ? "" : ", ");
        next = first + second;
        first = second;
        second = next;
    }
    std::cout << std::endl;

    return 0;
}