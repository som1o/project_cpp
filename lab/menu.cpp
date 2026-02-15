/**
 * Lab Menu Program - C++ Version
 * Provides a menu to calculate average, check leap year, or find GCD/LCM.
 */

#include <cstdlib>
#include <iostream>
#include <string>

// Function prototypes
void calculateAverage();
void checkLeapYear();
void findGCDandLCM();
bool readInt(const std::string &prompt, int &value);

int main() {
    int choice = 0;

    while (true) {
        std::cout << "\n--- Lab Toolkit Menu (C++) ---\n"
                  << "1. Calculate Average\n"
                  << "2. Check Leap Year\n"
                  << "3. Find GCD and LCM\n"
                  << "4. Exit\n";
        if (!readInt("Enter choice: ", choice)) {
            continue;
        }

        if (choice == 4) {
            std::cout << "Exiting program. Goodbye!" << std::endl;
            break;
        }

        switch (choice) {
            case 1:
                calculateAverage();
                break;
            case 2:
                checkLeapYear();
                break;
            case 3:
                findGCDandLCM();
                break;
            default:
                std::cout << "Invalid choice. Please select 1-4." << std::endl;
                break;
        }
    }

    return 0;
}

/**
 * Reads n numbers and displays their average.
 */
void calculateAverage() {
    int n;
    double sum = 0, num;

    std::cout << "\n[Average Calculator]\n";
    if (!readInt("Enter number of elements: ", n) || n <= 0) {
        std::cerr << "Error: Invalid number of elements." << std::endl;
        return;
    }

    std::cout << "Enter " << n << " numbers:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Number " << i + 1 << ": ";
        if (!(std::cin >> num)) {
            std::cerr << "Error: Invalid numeric input." << std::endl;
            return;
        }
        sum += num;
    }

    std::cout << "Success! The average is: " << (sum / n) << std::endl;
}

/**
 * Checks if a given year is a leap year.
 */
void checkLeapYear() {
    int year;

    std::cout << "\n[Leap Year Checker]\n";
    if (!readInt("Enter year: ", year)) {
        std::cerr << "Error: Invalid year." << std::endl;
        return;
    }

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        std::cout << year << " is a Leap Year." << std::endl;
    } else {
        std::cout << year << " is not a Leap Year." << std::endl;
    }
}

/**
 * Calculates Greatest Common Divisor and Least Common Multiple of two numbers.
 */
void findGCDandLCM() {
    int a, b;

    std::cout << "\n[GCD & LCM Finder]\n";
    if (!readInt("Enter first number: ", a) || !readInt("Enter second number: ", b)) {
        std::cerr << "Error: Invalid input." << std::endl;
        return;
    }

    int x = std::abs(a);
    int y = std::abs(b);
    // Euclidean algorithm for GCD
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }

    int gcd = x;
    long long lcm = gcd == 0 ? 0 : (static_cast<long long>(std::abs(a)) / gcd) * std::abs(b);

    std::cout << "Results for " << a << " and " << b << ":\n"
              << "GCD: " << gcd << "\n"
              << "LCM: " << lcm << std::endl;
}

bool readInt(const std::string &prompt, int &value) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter a whole number." << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}
