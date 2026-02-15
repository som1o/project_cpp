/**
 * Problem: A class of ten students took a quiz. Determine the class average.
 */

#include <iomanip>
#include <iostream>

int main() {
  int sum = 0;
  int grade;
  const int num_students = 10;

  std::cout << "Enter grades for " << num_students << " students:" << std::endl;
  for (int i = 0; i < num_students; i++) {
    std::cout << "Grade " << i + 1 << ": ";
    if (!(std::cin >> grade)) {
      std::cout << "Error: Invalid input." << std::endl;
      return 1;
    }
    sum += grade;
  }

  float average = static_cast<float>(sum) / num_students;
  std::cout << "Class Average: " << std::fixed << std::setprecision(2)
            << average << std::endl;

  return 0;
}
