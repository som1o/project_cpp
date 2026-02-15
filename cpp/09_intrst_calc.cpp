/**
 * Compound Interest Calculator
 * Calculates the amount on deposit for 10 years at 5% interest rate.
 */

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  double principal = 1000.0;
  double rate = 0.05;

  std::cout << std::left << std::setw(5) << "Year" << " " << "Amount on deposit"
            << std::endl;

  for (int year = 1; year <= 10; year++) {
    double amount = principal * pow(1.0 + rate, year);
    std::cout << std::left << std::setw(5) << year << " " << std::fixed
              << std::setprecision(2) << amount << std::endl;
  }

  return 0;
}
