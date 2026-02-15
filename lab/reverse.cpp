/**
 * Program to reverse the digits of an integer.
 */

#include <iostream>

int main() {
    int n, reversed = 0;

    std::cout << "Enter an integer to reverse: ";
    if (!(std::cin >> n)) {
        std::cerr << "Error: Invalid input." << std::endl;
        return 1;
    }

    int original = n;
    while (n != 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }

    std::cout << "Original: " << original << std::endl;
    std::cout << "Reversed: " << reversed << std::endl;

    return 0;
}