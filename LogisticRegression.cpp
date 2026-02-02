#include "LogisticRegression.h"

// Constructor
LogisticRegression::LogisticRegression(double lr, int iter)
    : learningRate(lr), iterations(iter), bias(0.0) {}

// Sigmoid Helper
double LogisticRegression::sigmoid(double z) {
  return 1.0 / (1.0 + std::exp(-z));
}

// Training: Gradient Descent
void LogisticRegression::train(const std::vector<std::vector<double>> &features,
                               const std::vector<int> &labels) {
  if (features.empty() || features.size() != labels.size()) {
    std::cerr << "Error: Invalid training data size.\n";
    return;
  }

  int nSamples = features.size();
  int nFeatures = features[0].size();

  // Initialize weights to 0
  weights.assign(nFeatures, 0.0);
  bias = 0.0;

  // Gradient Descent
  for (int i = 0; i < iterations; ++i) {
    std::vector<double> dw(nFeatures, 0.0);
    double db = 0.0;

    for (int j = 0; j < nSamples; ++j) {
      // Linear combination: z = w*x + b
      double z = bias;
      for (int k = 0; k < nFeatures; ++k) {
        z += weights[k] * features[j][k];
      }

      // Prediction
      double y_pred = sigmoid(z);

      // Error
      double error = y_pred - labels[j];

      // Gradients
      for (int k = 0; k < nFeatures; ++k) {
        dw[k] += error * features[j][k];
      }
      db += error;
    }

    // Update parameters
    for (int k = 0; k < nFeatures; ++k) {
      weights[k] -= learningRate * (dw[k] / nSamples);
    }
    bias -= learningRate * (db / nSamples);
  }
}

// Predict probability
double LogisticRegression::predictProba(const std::vector<double> &input) {
  if (input.size() != weights.size()) {
    std::cerr << "Error: Input feature size mismatch.\n";
    return 0.0;
  }

  double z = bias;
  for (size_t i = 0; i < weights.size(); ++i) {
    z += weights[i] * input[i];
  }
  return sigmoid(z);
}

// Predict Class
int LogisticRegression::predict(const std::vector<double> &input,
                                double threshold) {
  return predictProba(input) >= threshold ? 1 : 0;
}
