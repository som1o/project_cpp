/**
 * Program to calculate the sum of array elements using a function.
 */

#include <iomanip>
#include <iostream>

/**
 * Function to calculate the sum of a double array.
 * @param x Array of doubles.
 * @param n Number of elements.
 * @return The sum.
 */
double calculate_sum(const double x[], int n) {
  double total = 0.0;
  for (int i = 0; i < n; i++) {
    total += x[i];
  }
  return total;
}

int main() {
  double data[] = {3.0, 2.0, 4.0, 5.0};
  int num_elements = 4;
  double result;

  result = calculate_sum(data, num_elements);
  std::cout << "Sum: " << std::fixed << std::setprecision(2) << result
            << std::endl;

  return 0;
}

// Task-1: Modify the code to write a function to calculate the average.

// Task-2: Modify the code to write a function to calculate the median.

// HomeWork: Modify the code to write a fuction to calculate the IQR.
