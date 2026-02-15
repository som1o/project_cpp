/**
 * Program to print a right-angled triangle pattern of asterisks.
 */

#include <iostream>

int main() {
  const int height = 5;

  // Outer loop for rows
  for (int i = 1; i <= height; i++) {
    // Inner loop for columns
    for (int j = 1; j <= i; j++) {
      std::cout << "*";
    }
    std::cout << std::endl;
  }

  return 0;
}
