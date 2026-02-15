/**
 * Program to find the sum of numbers squared from 1 to n.
 */

#include <iostream>

int main() {
  int n, sum = 0;

  std::cout << "Enter a number (n): ";
  if (!(std::cin >> n)) {
    std::cout << "Error: Invalid input." << std::endl;
    return 1;
  }

  // Calculate sum of squares
  for (int i = 1; i <= n; i++) {
    sum += (i * i);
  }

  std::cout << "Sum of squares from 1 to " << n << ": " << sum << std::endl;

  return 0;
}
