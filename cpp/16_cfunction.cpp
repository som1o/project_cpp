/**
 * Program to determine the largest of three numbers.
 * Demonstrates basic function usage with multiple parameters.
 */

#include <iostream>

/**
 * Function to find the maximum of three integers.
 * @param val1 First integer.
 * @param val2 Second integer.
 * @param val3 Third integer.
 * @return The largest value among val1, val2, and val3.
 */
int find_max(int val1, int val2, int val3);

int main() {
  int x, y, z;

  std::cout << "Enter three integers: ";
  if (!(std::cin >> x >> y >> z)) {
    std::cout << "Error: Invalid input." << std::endl;
    return 1;
  }

  std::cout << "The maximum value is: " << find_max(x, y, z) << std::endl;
  return 0;
}

int find_max(int val1, int val2, int val3) {
  int maximum = val1;

  if (val2 > maximum) {
    maximum = val2;
  }
  if (val3 > maximum) {
    maximum = val3;
  }

  return maximum;
}
