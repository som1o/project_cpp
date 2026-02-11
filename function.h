#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>
#include <map>

struct Earthquake {
    double magnitude;
    int year;
    std::string region;
    int deaths;
};

std::vector<Earthquake> loadData(const std::string& filename);
void showStats(const std::vector<Earthquake>& data);
void showFrequencyTable(const std::vector<Earthquake>& data);
void runLinearRegression(const std::vector<Earthquake>& data);
double predictMagnitude(double slope, double intercept, int year);
std::string getSafetyOutlook(double slope);
double calculatePoisson(const std::vector<Earthquake>& data, double magThreshold, double years);

#endif
