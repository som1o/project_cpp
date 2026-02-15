#include "functions.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream file("inc2.csv");
  if (!file.is_open()) {
    std::cerr << "No such file there!" << std::endl;
    return 1;
  }

  std::string line;
  std::vector<double> income, expenditure, savings;
  int id;
  double inc, exp, sav;

  // Skip header
  std::getline(file, line);

  while (std::getline(file, line)) {
    if (line.empty())
      continue;
    char comma;
    std::stringstream ss(line);
    // CSV format: id,income,expenditure,savings
    if (ss >> id >> comma >> inc >> comma >> exp >> comma >> sav) {
      income.push_back(inc);
      expenditure.push_back(exp);
      savings.push_back(sav);
    }
  }
  file.close();

  if (income.empty()) {
    std::cout << "No data found." << std::endl;
    return 0;
  }

  std::cout << "Mean Income: " << std::fixed << std::setprecision(2)
            << mean(income) << std::endl;
  std::cout << "Mean Expenditure: " << mean(expenditure) << std::endl;
  std::cout << "Mean Savings: " << mean(savings) << std::endl;
  std::cout << "2nd Raw Moment (Income): " << moment(income, 2) << std::endl;
  std::cout << "3rd Raw Moment (Expenditure): " << moment(expenditure, 3)
            << std::endl;

  double var_inc = variance(income);
  double var_exp = variance(expenditure);

  std::cout << "Variance(Income): " << var_inc
            << ", Variance(Expenditure): " << var_exp << std::endl;
  std::cout << "Cov(Income, Expenditure): " << covariance(income, expenditure)
            << std::endl;
  std::cout << "Cov(Income, Savings): " << covariance(income, savings)
            << std::endl;
  std::cout << "Correlation(Income, Expenditure): " << std::setprecision(4)
            << correlation(income, expenditure) << std::endl;
  std::cout << "Correlation(Income, Savings): " << correlation(income, savings)
            << std::endl;
  std::cout << "Correlation(Savings, Expenditure): "
            << correlation(savings, expenditure) << std::endl;

  return 0;
}
