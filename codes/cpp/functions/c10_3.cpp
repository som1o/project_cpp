/**
 * Program to calculate various statistics (sum, average, maximum) of an array.
 * Demonstrates returning multiple values via pointers.
 */

#include <iomanip>
#include <iostream>

/**
 * Calculates sum, average, and maximum of an array.
 * @param x The input array.
 * @param n Number of elements.
 * @param sum Pointer to store the sum.
 * @param avg Pointer to store the average.
 * @param max Pointer to store the maximum value.
 */
void calculate_stats(const double x[], int n, double *sum, double *avg,
                     double *max) {
  if (n <= 0)
    return;

  *sum = 0.0;
  *max = x[0];

  for (int i = 0; i < n; i++) {
    *sum += x[i];
    if (x[i] > *max) {
      *max = x[i];
    }
  }

  *avg = *sum / n;
}

int main() {
  double data[] = {3.0, 2.0, 4.0, 5.0};
  int num_elements = 4;
  double sum = 0.0, average = 0.0, maximum = 0.0;

  calculate_stats(data, num_elements, &sum, &average, &maximum);

  std::cout << "Array Statistics:" << std::endl;
  std::cout << "Sum:      " << std::fixed << std::setprecision(2) << sum
            << std::endl;
  std::cout << "Average:  " << average << std::endl;
  std::cout << "Maximum:  " << maximum << std::endl;

  return 0;
}
