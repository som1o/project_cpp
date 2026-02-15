#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

double mean(const std::vector<double> &x);
double moment(const std::vector<double> &x, int r);
double variance(const std::vector<double> &x);
double covariance(const std::vector<double> &x, const std::vector<double> &y);
double correlation(const std::vector<double> &x, const std::vector<double> &y);

#endif