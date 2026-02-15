/**
 * Program demonstrating a user-defined function.
 * Calculates and prints the square of numbers from 1 to n.
 */

#include <iostream>

/**
 * Function to calculate the square of an integer.
 * @param val The integer to be squared.
 * @return The square of val.
 */
int calculate_square(int val);

int main() {
  int n;

  std::cout << "Enter a number (n): ";
  if (!(std::cin >> n)) {
    std::cout << "Error: Invalid input." << std::endl;
    return 1;
  }

  for (int i = 1; i <= n; i++) {
    std::cout << "Square of " << i << " is " << calculate_square(i)
              << std::endl;
  }

  return 0;
}

int calculate_square(int val) { return val * val; }
