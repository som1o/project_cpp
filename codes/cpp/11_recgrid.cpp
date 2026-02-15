/**
 * Program to print a 5x4 grid of asterisks.
 */

#include <iostream>

int main() {
  // Print a 5 (rows) x 4 (columns) rectangle
  for (int row = 1; row <= 5; row++) {
    for (int col = 1; col <= 4; col++) {
      std::cout << "*";
    }
    std::cout << std::endl;
  }

  return 0;
}
