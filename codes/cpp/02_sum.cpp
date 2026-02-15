#include <iostream>

/**
 * Program to calculate the sum of two integers.
 */
int main() {
  int num1, num2;

  std::cout << "Enter two integers: ";
  if (std::cin >> num1 >> num2) {
    std::cout << "Sum: " << num1 + num2 << std::endl;
  } else {
    std::cout << "Error: Invalid input." << std::endl;
  }

  return 0;
}
