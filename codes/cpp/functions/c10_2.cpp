/**
 * Program to calculate the sum and average of array elements using a
 * pointer-based function.
 */

#include <iomanip>
#include <iostream>

/**
 * Function to calculate the sum of a double array using a pointer.
 * @param x Array of doubles.
 * @param n Number of elements.
 * @param sum_ptr Pointer to a double where the sum will be stored.
 */
void calculate_sum_ptr(const double x[], int n, double *sum_ptr) {
  *sum_ptr = 0.0;
  for (int i = 0; i < n; i++) {
    *sum_ptr += x[i];
  }
}

int main() {
  double data[] = {3.0, 2.0, 4.0, 5.0};
  double sum = 0.0;
  int num_elements = 4;

  calculate_sum_ptr(data, num_elements, &sum);

  std::cout << "Sum:     " << std::fixed << std::setprecision(2) << sum
            << std::endl;
  std::cout << "Average: " << sum / num_elements << std::endl;

  return 0;
}
