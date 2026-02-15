#include <iostream>
#include <string>

/**
 * A simple calculator program that takes an operator and two integers
 * and performs the corresponding arithmetic operation.
 */
double readNumber(const std::string &prompt, bool &ok) {
  double value = 0.0;
  std::cout << prompt;
  if (!(std::cin >> value)) {
    std::cout << "Error: Invalid numeric input." << std::endl;
    ok = false;
    return 0.0;
  }
  ok = true;
  return value;
}

int main() {
  char op = '\0';
  bool ok = true;

  std::cout << "Enter an operator (+, -, *, /): ";
  if (!(std::cin >> op)) {
    std::cout << "Error: Invalid operator input." << std::endl;
    return 1;
  }

  double num1 = readNumber("Enter the first number: ", ok);
  if (!ok) {
    return 1;
  }
  double num2 = readNumber("Enter the second number: ", ok);
  if (!ok) {
    return 1;
  }

  switch (op) {
  case '+':
    std::cout << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;
    break;
  case '-':
    std::cout << num1 << " - " << num2 << " = " << num1 - num2 << std::endl;
    break;
  case '*':
    std::cout << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
    break;
  case '/':
    if (num2 != 0) {
      std::cout << num1 << " / " << num2 << " = " << num1 / num2 << std::endl;
    } else {
      std::cout << "Error: Division by zero is not possible." << std::endl;
    }
    break;
  default:
    std::cout << "Error: Unknown operator '" << op << "'." << std::endl;
    break;
  }

  return 0;
}
