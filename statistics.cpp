#include "Earthquake.h"

int safeToInt(const std::string &s) {
  if (s.empty() || s == "NA")
    return 0;
  try {
    return std::stoi(s);
  } catch (...) {
    return 0;
  }
}

double safeToDouble(const std::string &s) {
  if (s.empty() || s == "NA")
    return 0.0;
  try {
    return std::stod(s);
  } catch (...) {
    return 0.0;
  }
}

std::string trim(const std::string &str) {
  size_t start = str.find_first_not_of(" \t\r\n");
  if (start == std::string::npos)
    return "";
  size_t end = str.find_last_not_of(" \t\r\n");
  return str.substr(start, end - start + 1);
}

bool loadData(const std::string &filename, std::vector<Earthquake> &data) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Cannot open file '" << filename << "'\n";
    return false;
  }

  std::string line;
  std::getline(file, line); // skip header

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::stringstream ss(line);
    std::string value;
    Earthquake eq;

    std::getline(ss, value, ',');
    eq.magnitude = safeToDouble(trim(value));
    std::getline(ss, value, ',');
    eq.year = safeToInt(trim(value));
    std::getline(ss, value, ',');
    eq.origin = trim(value);
    std::getline(ss, value, ',');
    eq.region = trim(value);
    std::getline(ss, value, ',');
    eq.deaths = safeToInt(trim(value));
    std::getline(ss, value, ',');
    eq.injuries = safeToInt(trim(value));
    std::getline(ss, value, ',');
    eq.damages = safeToInt(trim(value));
    std::getline(ss, value, ',');
    eq.socioeconomicLevel = safeToInt(trim(value));

    data.push_back(eq);
  }

  return !data.empty();
}

double calculateMean(const std::vector<double> &values) {
  if (values.empty())
    return 0.0;
  double sum = 0.0;
  for (const auto &v : values)
    sum += v;
  return sum / values.size();
}

double calculateStdDev(const std::vector<double> &values, double mean) {
  if (values.empty())
    return 0.0;
  double variance = 0.0;
  for (const auto &v : values) {
    variance += (v - mean) * (v - mean);
  }
  return std::sqrt(variance / values.size());
}

double calculateBValue(const std::vector<Earthquake> &data, double minMagnitude,
                       double maxMagnitude) {
  /*
   * Gutenberg-Richter Law: log10(N) = a - b*M
   * The b-value indicates stress levels in fault segments.
   * A declining b-value suggests increasing stress.
   */
  std::vector<double> magnitudes;
  for (const auto &eq : data) {
    if (eq.magnitude >= minMagnitude && eq.magnitude <= maxMagnitude) {
      magnitudes.push_back(eq.magnitude);
    }
  }

  if (magnitudes.empty())
    return 0.0;

  double meanMag = calculateMean(magnitudes);
  double minMag = *std::min_element(magnitudes.begin(), magnitudes.end());

  double bValue = 1.0 / (std::log(10.0) * (meanMag - minMag));
  return std::abs(bValue);
}

double poissonProbability(int k, double lambda) {
  if (lambda <= 0)
    return 0.0;
  double prob = std::exp(-lambda) * std::pow(lambda, k);
  for (int i = 1; i <= k; ++i) {
    prob /= i;
  }
  return prob;
}

double calculateReturnPeriod(const std::vector<Earthquake> &data,
                             double minMagnitude) {
  if (data.empty())
    return std::numeric_limits<double>::infinity();

  int count = 0;
  int minYear = std::numeric_limits<int>::max();
  int maxYear = std::numeric_limits<int>::min();

  for (const auto &eq : data) {
    if (eq.year > 0) {
      minYear = std::min(minYear, eq.year);
      maxYear = std::max(maxYear, eq.year);
    }
    if (eq.magnitude >= minMagnitude)
      count++;
  }

  int yearsOfObservation = maxYear - minYear + 1;
  if (count == 0 || yearsOfObservation <= 0) {
    return std::numeric_limits<double>::infinity();
  }

  return static_cast<double>(yearsOfObservation) / count;
}

double pearsonCorrelation(const std::vector<double> &x,
                          const std::vector<double> &y) {
  if (x.size() != y.size() || x.empty())
    return 0.0;

  size_t n = x.size();
  double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, sumY2 = 0;

  for (size_t i = 0; i < n; ++i) {
    sumX += x[i];
    sumY += y[i];
    sumXY += x[i] * y[i];
    sumX2 += x[i] * x[i];
    sumY2 += y[i] * y[i];
  }

  double numerator = n * sumXY - sumX * sumY;
  double denominator =
      std::sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));

  if (denominator == 0)
    return 0.0;
  return numerator / denominator;
}

void linearRegression(const std::vector<double> &x,
                      const std::vector<double> &y, double &slope,
                      double &intercept) {
  slope = 0.0;
  intercept = 0.0;

  if (x.size() != y.size() || x.empty())
    return;

  size_t n = x.size();
  double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

  for (size_t i = 0; i < n; ++i) {
    sumX += x[i];
    sumY += y[i];
    sumXY += x[i] * y[i];
    sumX2 += x[i] * x[i];
  }

  double denominator = n * sumX2 - sumX * sumX;
  if (denominator == 0)
    return;

  slope = (n * sumXY - sumX * sumY) / denominator;
  intercept = (sumY - slope * sumX) / n;
}

RiskTier classifyRisk(const Earthquake &eq) {
  /*
   * Risk Classification based on:
   * - Magnitude: Higher magnitude = higher risk
   * - Socioeconomic Level: Lower level = higher vulnerability
   *
   * Risk Score = Magnitude * (4 - SocioeconomicLevel)
   * Tiers: LOW (<15), MEDIUM (15-25), HIGH (>25)
   */
  double riskScore = eq.magnitude * (4 - eq.socioeconomicLevel);

  if (riskScore >= 25.0)
    return RiskTier::HIGH;
  if (riskScore >= 15.0)
    return RiskTier::MEDIUM;
  return RiskTier::LOW;
}

std::string riskTierToString(RiskTier tier) {
  switch (tier) {
  case RiskTier::HIGH:
    return "HIGH";
  case RiskTier::MEDIUM:
    return "MEDIUM";
  case RiskTier::LOW:
    return "LOW";
  default:
    return "UNKNOWN";
  }
}

std::string getMostActiveRegion(const std::vector<Earthquake> &data,
                                int &count) {
  std::map<std::string, int> regionCounts = getRegionCounts(data);

  std::string maxRegion;
  count = 0;

  for (const auto &pair : regionCounts) {
    if (pair.second > count) {
      count = pair.second;
      maxRegion = pair.first;
    }
  }

  return maxRegion;
}

std::map<std::string, int>
getRegionCounts(const std::vector<Earthquake> &data) {
  std::map<std::string, int> counts;
  for (const auto &eq : data) {
    counts[eq.region]++;
  }
  return counts;
}

double calculateAnnualRate(const std::vector<Earthquake> &data,
                           double minMagnitude) {
  if (data.empty())
    return 0.0;

  int count = 0;
  int minYear = std::numeric_limits<int>::max();
  int maxYear = std::numeric_limits<int>::min();

  for (const auto &eq : data) {
    if (eq.year > 0) {
      minYear = std::min(minYear, eq.year);
      maxYear = std::max(maxYear, eq.year);
    }
    if (eq.magnitude >= minMagnitude)
      count++;
  }

  int yearsOfObservation = maxYear - minYear + 1;
  if (yearsOfObservation <= 0)
    return 0.0;

  return static_cast<double>(count) / yearsOfObservation;
}

void displayInteractiveProbability(const std::vector<Earthquake> &data) {
  printHeader("INTERACTIVE PROBABILITY CALCULATOR");

  std::cout << "  Enter a Magnitude threshold (e.g., 6.0): ";
  double inputMag;
  while (!(std::cin >> inputMag)) {
    std::cout << "  Invalid input. Please enter a number: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  std::cout << "  Enter Time Period in years (e.g., 50): ";
  double inputYears;
  while (!(std::cin >> inputYears) || inputYears <= 0) {
    std::cout << "  Invalid input. Please enter a positive number: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  double lambda = calculateAnnualRate(data, inputMag);

  if (lambda <= 0.0) {
    std::cout << "\n  [!] No historical events found with M >= " << inputMag
              << ".\n";
    std::cout << "      Probability estimation is not possible without "
                 "historical data.\n";
  } else {
    // P(at least one event) = 1 - P(0 events) = 1 - e^(-lambda * t)
    // Expected number of events = lambda * t
    double expectedEvents = lambda * inputYears;
    double probability = 1.0 - std::exp(-expectedEvents);

    std::cout << "\n  --- RESULTS ---\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "  Historical Annual Rate (M >= " << std::setprecision(1)
              << inputMag << "): " << std::setprecision(4) << lambda
              << " events/year\n";
    std::cout << "  Expected events in " << std::setprecision(1) << inputYears
              << " years: " << std::setprecision(4) << expectedEvents << "\n";
    std::cout << "  Probability of at least one event: " << std::setprecision(2)
              << (probability * 100.0) << "%\n";
  }
}

void printSeparator() { std::cout << std::string(50, '-') << "\n"; }

void printHeader(const std::string &title) {
  std::cout << "\n";
  printSeparator();
  std::cout << "  " << title << "\n";
  printSeparator();
}
