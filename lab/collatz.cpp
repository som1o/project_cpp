/**
 * Program to generate the Collatz sequence for a given number.
 * If n is even, n = n / 2. If n is odd, n = 3n + 1.
 */

#include <iostream>

int main() {
    int n;

    std::cout << "Enter a starting number for Collatz sequence: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Error: Please enter a positive integer." << std::endl;
        return 1;
    }

    std::cout << "Sequence: ";
    while (n != 1) {
        std::cout << n << " -> ";
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
    }
    std::cout << "1" << std::endl;

    return 0;
}