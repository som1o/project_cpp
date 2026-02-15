/**
 * Program to display numbers from 1 to n.
 */

#include <iostream>

int main() {
  int n;

  std::cout << "Enter a number (n): ";
  if (!(std::cin >> n)) {
    std::cout << "Error: Invalid input." << std::endl;
    return 1;
  }

  // Display numbers from 1 to n
  for (int i = 1; i <= n; i++) {
    std::cout << i << std::endl;
  }

  return 0;
}
