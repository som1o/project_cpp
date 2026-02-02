#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// Simple Logistic Regression Class
class LogisticRegression {
private:
  std::vector<double> weights;
  double bias;
  double learningRate;
  int iterations;

  // Sigmoid function: 1 / (1 + e^-z)
  double sigmoid(double z);

public:
  LogisticRegression(double lr = 0.01, int iter = 1000);

  // Train the model
  // features: vector of input vectors (e.g., [[mag1, socio1], [mag2, socio2]])
  // labels: vector of actual outcomes (0 or 1)
  void train(const std::vector<std::vector<double>> &features,
             const std::vector<int> &labels);

  // Predict probability (0.0 to 1.0)
  double predictProba(const std::vector<double> &input);

  // Predict class (0 or 1)
  int predict(const std::vector<double> &input, double threshold = 0.5);

  // Getters for debugging
  std::vector<double> getWeights() const { return weights; }
  double getBias() const { return bias; }
};

#endif
