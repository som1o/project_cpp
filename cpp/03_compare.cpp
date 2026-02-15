#include <iostream>

/**
 * Program to compare two numbers and print messages based on the result.
 */
int main() {
  int num1, num2;

  std::cout << "Enter two integers to compare: ";
  if (!(std::cin >> num1 >> num2)) {
    std::cout << "Error: Invalid input." << std::endl;
    return 1;
  }

  if (num1 == num2) {
    std::cout << "The numbers are equal! Printing a bonus message 10 times:"
              << std::endl;
    for (int i = 0; i < 10; i++) {
      std::cout << "Success!" << std::endl;
    }
  } else {
    std::cout << "The numbers are different." << std::endl;
  }

  return 0;
}
