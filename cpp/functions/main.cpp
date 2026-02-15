/**
 * Program demonstrating function calls for summing array elements.
 * Uses both pointer-based and value-returning functions.
 */

#include <iomanip>
#include <iostream>

/**
 * Calculates the sum of elements in an array.
 * @param x The array of doubles.
 * @param n The number of elements.
 * @return The sum as a double.
 */
double calculate_sum(const double x[], int n);

/**
 * Calculates the sum of elements in an array using a pointer.
 * @param x The array of doubles.
 * @param n The number of elements.
 * @param s Pointer to a double where the sum will be stored.
 */
void calculate_sum_ptr(const double x[], int n, double *s);

int main() {
  double data[] = {3.0, 2.0, 4.0, 5.0};
  double sum_ptr = 0.0;
  double sum_val;
  int num_elements = 4;

  calculate_sum_ptr(data, num_elements, &sum_ptr);
  sum_val = calculate_sum(data, num_elements);

  std::cout << "Sum using pointer:    " << std::fixed << std::setprecision(2)
            << sum_ptr << std::endl;
  std::cout << "Sum without pointer:  " << sum_val << std::endl;

  return 0;
}
