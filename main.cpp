#include "function.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cmath>

int main() {
    auto data = loadData("earthquakes.csv");
    if (data.empty()) {
        std::cout << "Hi! It seems I couldn't find any earthquake data to analyze. Please check if 'earthquakes.csv' is ready.\n";
        return 1;
    }

    std::cout << "--- Welcome to the Earthquake Analysis System ---\n";
    std::cout << "I've carefully analyzed " << data.size() << " recorded events for you.\n";

    showStats(data);
    showFrequencyTable(data);
    
    // Manual Regression calculation to get parameters for prediction
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int n = data.size();
    for (const auto& eq : data) {
        sumX += eq.year;
        sumY += eq.magnitude;
        sumXY += (double)eq.year * eq.magnitude;
        sumX2 += (double)eq.year * eq.year;
    }
    double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double intercept = (sumY - slope * sumX) / n;

    std::cout << "\n--- Trend & Outlook ---\n";
    std::cout << getSafetyOutlook(slope) << "\n";

    std::cout << "\n--- Interactive Tools ---\n";
    int choice;
    while (true) {
        std::cout << "\nWhat would you like to explore next?\n";
        std::cout << "1. Predict earthquake intensity for a future year\n";
        std::cout << "2. Calculate the probability of an earthquake in a timeframe\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            int futureYear;
            std::cout << "Which year are you curious about? ";
            while (!(std::cin >> futureYear)) {
                std::cout << "Please enter a valid year number: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            double pred = predictMagnitude(slope, intercept, futureYear);
            std::cout << "Based on historical trends, I estimate a potential magnitude of " << std::fixed << std::setprecision(2) << pred << " around " << futureYear << ".\n";
        } else if (choice == 2) {
            double mag, years;
            std::cout << "Magnitude threshold you're worried about (e.g., 6.0): ";
            while (!(std::cin >> mag)) {
                std::cout << "Please enter a number for magnitude: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "How many years into the future should I look? (e.g., 50): ";
            while (!(std::cin >> years)) {
                std::cout << "Please enter a number for years: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            double prob = calculatePoisson(data, mag, years);
            std::cout << "I've calculated a " << std::fixed << std::setprecision(2) << prob * 100.0 << "% chance that an earthquake of M" << mag << " or greater will occur in the next " << years << " years.\n";
        } else if (choice == 3) {
            std::cout << "Take care and stay safe! Goodbye.\n";
            break;
        }
    }

    return 0;
}
