/**
 * Program to process exam results.
 * Counts passes and failures among 10 students.
 */

#include <iostream>

int main() {
  int passes = 0;
  int failures = 0;
  int grade;

  std::cout << "Enter results (1 for pass, 2 for fail) for 10 students:"
            << std::endl;
  for (int i = 1; i <= 10; i++) {
    std::cout << "Student " << i << ": ";
    if (!(std::cin >> grade)) {
      std::cout << "Error: Invalid input." << std::endl;
      return 1;
    }

    if (grade == 1) {
      passes++;
    } else {
      failures++;
    }
  }

  std::cout << "\nExam Results Summary:" << std::endl;
  std::cout << "Passes: " << passes << std::endl;
  std::cout << "Failures: " << failures << std::endl;

  if (passes > 8) {
    std::cout << "Bonus to instructor!" << std::endl;
  }

  return 0;
}
