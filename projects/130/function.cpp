#include "function.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cmath>

std::vector<Earthquake> loadData(const std::string& filename) {
    std::vector<Earthquake> data;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string val;
        Earthquake eq;
        if (!std::getline(ss, val, ',')) continue;
        eq.magnitude = std::stod(val);
        if (!std::getline(ss, val, ',')) continue;
        eq.year = std::stoi(val);
        std::getline(ss, val, ',');
        if (!std::getline(ss, val, ',')) continue;
        eq.region = val;
        if (!std::getline(ss, val, ',')) continue;
        eq.deaths = std::stoi(val);
        data.push_back(eq);
    }
    return data;
}

void showStats(const std::vector<Earthquake>& data) {
    double sum = 0, maxMag = 0;
    for (const auto& eq : data) {
        sum += eq.magnitude;
        if (eq.magnitude > maxMag) maxMag = eq.magnitude;
    }
    std::cout << "\nBasic Stats:\nTotal: " << data.size() 
              << "\nAverage Magnitude: " << sum / data.size() 
              << "\nMax Magnitude: " << maxMag << "\n";
}

void showFrequencyTable(const std::vector<Earthquake>& data) {
    std::map<std::string, int> counts;
    for (const auto& eq : data) counts[eq.region]++;
    std::cout << "\nRegion Frequency Table:\n";
    for (auto const& [region, count] : counts)
        std::cout << std::left << std::setw(20) << region << ": " << count << "\n";
}

void runLinearRegression(const std::vector<Earthquake>& data) {
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
    std::cout << "\nTemporal Trend Analysis:\nSlope: " << slope 
              << "\nIntercept: " << intercept << "\n";
}

double predictMagnitude(double slope, double intercept, int year) {
    return slope * year + intercept;
}

std::string getSafetyOutlook(double slope) {
    if (slope > 0.005) return "Warning: Earthquake magnitudes show a noticeable upward trend over the years. We should stay vigilant.";
    if (slope < -0.005) return "Good news: We're seeing a slight downward trend in earthquake magnitudes lately.";
    return "The seismic trend seems stable, with no significant increase in earthquake intensity over time.";
}

double calculatePoisson(const std::vector<Earthquake>& data, double magThreshold, double years) {
    int count = 0;
    int minYear = 9999, maxYear = 0;
    for (const auto& eq : data) {
        if (eq.year > 0) {
            if (eq.year < minYear) minYear = eq.year;
            if (eq.year > maxYear) maxYear = eq.year;
        }
        if (eq.magnitude >= magThreshold) count++;
    }
    int range = maxYear - minYear + 1;
    if (range <= 0 || count == 0) return 0.0;
    double lambda = (double)count / range;
    return 1.0 - std::exp(-lambda * years);
}
