#include "functions.h"
#include <cmath>

#include <vector>

double mean(const std::vector<double> &x) {
  if (x.empty())
    return 0.0;
  double sum = 0;
  for (double val : x) {
    sum += val;
  }
  return sum / x.size();
}

double moment(const std::vector<double> &x, int r) {
  if (x.empty())
    return 0.0;
  double sum = 0;
  for (double val : x) {
    sum += std::pow(val, r);
  }
  return sum / x.size();
}

double variance(const std::vector<double> &x) {
  double m2 = moment(x, 2);
  double avg = mean(x);
  return m2 - (avg * avg);
}

double covariance(const std::vector<double> &x, const std::vector<double> &y) {
  size_t n = x.size();
  if (n != y.size() || n == 0)
    return 0.0;

  double sum_xy = 0;
  double avg_x = mean(x);
  double avg_y = mean(y);

  for (size_t i = 0; i < n; i++) {
    sum_xy += x[i] * y[i];
  }
  return (sum_xy / n) - (avg_x * avg_y);
}

double correlation(const std::vector<double> &x, const std::vector<double> &y) {
  double var_x = variance(x);
  double var_y = variance(y);
  if (var_x == 0 || var_y == 0)
    return 0.0;
  return covariance(x, y) / std::sqrt(var_x * var_y);
}
