/**
 * Program to calculate the sum and average of an array of size n.
 * Demonstrates basic array usage and indexing.
 */

#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  int num_elements;

  std::cout << "Enter the number of elements: ";
  if (!(std::cin >> num_elements) || num_elements <= 0) {
    std::cout << "Error: Invalid number of elements." << std::endl;
    return 1;
  }

  std::vector<int> arr(num_elements);
  int sum = 0;

  std::cout << "Enter " << num_elements << " integers:" << std::endl;
  for (int i = 0; i < num_elements; i++) {
    std::cout << "Element [" << i << "]: ";
    if (!(std::cin >> arr[i])) {
      std::cout << "Error: Invalid input." << std::endl;
      return 1;
    }
  }

  // Calculate sum
  for (int i = 0; i < num_elements; i++) {
    sum += arr[i];
  }

  float average = static_cast<float>(sum) / num_elements;
  std::cout << "\nSum: " << sum << std::endl;
  std::cout << "Average: " << std::fixed << std::setprecision(2) << average
            << std::endl;

  return 0;
}
