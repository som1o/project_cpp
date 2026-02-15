/**
 * Implementation of sum functions using different approaches.
 */

double calculate_sum(const double x[], int n) {
  double total = 0.0;
  for (int i = 0; i < n; i++) {
    total += x[i];
  }
  return total;
}

void calculate_sum_ptr(const double x[], int n, double *s) {
  *s = 0.0; // Ensure it starts at 0
  for (int i = 0; i < n; i++) {
    *s += x[i];
  }
}
