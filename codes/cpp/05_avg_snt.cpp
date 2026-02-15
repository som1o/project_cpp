/**
 * Problem: A class of n students took a quiz.
 * Determine the class average using a sentinel-controlled loop.
 */

#include <iomanip>
#include <iostream>

int main() {
  int count = 0;
  int grade;
  int sum = 0;

  std::cout << "Enter grades (enter -1 to finish):" << std::endl;

  // Sentinel controlled loop
  while (true) {
    std::cout << "Enter grade: ";
    if (!(std::cin >> grade)) {
      std::cout << "Error: Invalid input." << std::endl;
      // Clear buffer if necessary, but here we just exit for simplicity
      return 1;
    }

    if (grade == -1) {
      break;
    }

    sum += grade;
    count++;
  }

  if (count != 0) {
    float average = static_cast<float>(sum) / count;
    std::cout << "\nTotal students: " << count << std::endl;
    std::cout << "Class Average: " << std::fixed << std::setprecision(2)
              << average << std::endl;
  } else {
    std::cout << "\nNo grades were entered." << std::endl;
  }

  return 0;
}
