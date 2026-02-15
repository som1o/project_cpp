#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace {
bool readInt(const std::string &prompt, int &value) {
  std::cout << prompt;
  if (!(std::cin >> value)) {
    std::cout << "Error: Please enter a whole number." << std::endl;
    return false;
  }
  return true;
}

bool readDouble(const std::string &prompt, double &value) {
  std::cout << prompt;
  if (!(std::cin >> value)) {
    std::cout << "Error: Please enter a number." << std::endl;
    return false;
  }
  return true;
}
} // namespace

/**
 * Simple statistics storyteller.
 * Reads a list of numbers and prints a plain-language summary.
 */
int main() {
  int count = 0;
  if (!readInt("How many numbers should I summarize? ", count) || count <= 0) {
    std::cout << "Please enter a positive amount." << std::endl;
    return 1;
  }

  std::vector<double> values;
  values.reserve(static_cast<size_t>(count));

  for (int i = 0; i < count; ++i) {
    double value = 0.0;
    if (!readDouble("Number " + std::to_string(i + 1) + ": ", value)) {
      return 1;
    }
    values.push_back(value);
  }

  double sum = 0.0;
  for (double value : values) {
    sum += value;
  }

  std::sort(values.begin(), values.end());
  double mean = sum / values.size();
  double median = 0.0;
  if (values.size() % 2 == 1) {
    median = values[values.size() / 2];
  } else {
    size_t mid = values.size() / 2;
    median = (values[mid - 1] + values[mid]) / 2.0;
  }

  double minValue = values.front();
  double maxValue = values.back();

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "\nSummary:\n";
  std::cout << "- Smallest value: " << minValue << "\n";
  std::cout << "- Largest value: " << maxValue << "\n";
  std::cout << "- Total of all values: " << sum << "\n";
  std::cout << "- Average (mean): " << mean << "\n";
  std::cout << "- Middle value (median): " << median << "\n";

  return 0;
}
