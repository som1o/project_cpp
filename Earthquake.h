#ifndef EARTHQUAKE_H
#define EARTHQUAKE_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Earthquake {
  double magnitude;
  int year;
  std::string origin;
  std::string region;
  int deaths;
  int injuries;
  int damages;
  int socioeconomicLevel;
};

enum class RiskTier { LOW, MEDIUM, HIGH };

int safeToInt(const std::string &s);
double safeToDouble(const std::string &s);

bool loadData(const std::string &filename, std::vector<Earthquake> &data);

double calculateMean(const std::vector<double> &values);
double calculateStdDev(const std::vector<double> &values, double mean);

double calculateBValue(const std::vector<Earthquake> &data, double minMagnitude,
                       double maxMagnitude);

double poissonProbability(int k, double lambda);
double calculateAnnualRate(const std::vector<Earthquake> &data,
                           double minMagnitude);
double calculateReturnPeriod(const std::vector<Earthquake> &data,
                             double minMagnitude);

double pearsonCorrelation(const std::vector<double> &x,
                          const std::vector<double> &y);

void linearRegression(const std::vector<double> &x,
                      const std::vector<double> &y, double &slope,
                      double &intercept);

RiskTier classifyRisk(const Earthquake &eq);
std::string riskTierToString(RiskTier tier);

std::string getMostActiveRegion(const std::vector<Earthquake> &data,
                                int &count);
std::map<std::string, int> getRegionCounts(const std::vector<Earthquake> &data);

void printSeparator();
void printHeader(const std::string &title);
void displayInteractiveProbability(const std::vector<Earthquake> &data);

#endif
