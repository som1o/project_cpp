#include "Earthquake.h"

void displayBasicStats(const std::vector<Earthquake> &data);
void displayGutenbergRichter(const std::vector<Earthquake> &data);
void displayPoissonAnalysis(const std::vector<Earthquake> &data);
void displayCorrelationAnalysis(const std::vector<Earthquake> &data);
void displayRegressionAnalysis(const std::vector<Earthquake> &data);
void displayRegionalAnalysis(const std::vector<Earthquake> &data);
void displayRiskClassification(const std::vector<Earthquake> &data);
void displayFullReport(const std::vector<Earthquake> &data);

int main() {
  std::vector<Earthquake> data;

  if (!loadData("earthquakes.csv", data)) {
    std::cerr << "Failed to load earthquake data.\n";
    return 1;
  }

  std::cout << "\n";
  std::cout << "======================================================\n";
  std::cout << "   SEISMIC INTELLIGENCE ANALYSIS SYSTEM\n";
  std::cout << "   Bangladesh Earthquake Risk Assessment\n";
  std::cout << "======================================================\n";

  displayFullReport(data);
  displayInteractiveProbability(data);

  return 0;
}

void displayBasicStats(const std::vector<Earthquake> &data) {
  printHeader("BASIC STATISTICS");

  std::vector<double> magnitudes;
  for (const auto &eq : data)
    magnitudes.push_back(eq.magnitude);

  double mean = calculateMean(magnitudes);
  double stddev = calculateStdDev(magnitudes, mean);

  double minMag = *std::min_element(magnitudes.begin(), magnitudes.end());
  double maxMag = *std::max_element(magnitudes.begin(), magnitudes.end());

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "  Total Earthquakes Analyzed: " << data.size() << "\n";
  std::cout << "  Magnitude Range: " << minMag << " - " << maxMag << "\n";
  std::cout << "  Mean Magnitude: " << mean << "\n";
  std::cout << "  Standard Deviation: " << stddev << "\n";

  int minYear = std::numeric_limits<int>::max();
  int maxYear = std::numeric_limits<int>::min();
  for (const auto &eq : data) {
    if (eq.year > 0) {
      minYear = std::min(minYear, eq.year);
      maxYear = std::max(maxYear, eq.year);
    }
  }
  std::cout << "  Time Period: " << minYear << " - " << maxYear << " ("
            << (maxYear - minYear + 1) << " years)\n";
}

void displayGutenbergRichter(const std::vector<Earthquake> &data) {
  printHeader("GUTENBERG-RICHTER ANALYSIS");

  double bValue = calculateBValue(data, 4.0, 9.0);

  std::cout << std::fixed << std::setprecision(3);
  std::cout << "  Relationship: log10(N) = a - b*M\n";
  std::cout << "  Calculated b-value: " << bValue << "\n";
  std::cout << "\n  Interpretation:\n";

  if (bValue < 0.8) {
    std::cout << "    Low b-value suggests HIGH stress accumulation.\n";
    std::cout << "    Increased probability of large magnitude events.\n";
  } else if (bValue > 1.2) {
    std::cout << "    High b-value indicates NORMAL stress release.\n";
    std::cout << "    Frequent small events, fewer large ones expected.\n";
  } else {
    std::cout << "    Moderate b-value indicates TYPICAL seismic behavior.\n";
    std::cout << "    Standard frequency-magnitude distribution.\n";
  }
}

void displayPoissonAnalysis(const std::vector<Earthquake> &data) {
  printHeader("POISSON PROBABILITY MODEL");

  int majorEvents = 0;
  for (const auto &eq : data) {
    if (eq.magnitude >= 7.0)
      majorEvents++;
  }

  double returnPeriod = calculateReturnPeriod(data, 7.0);
  double lambda = 1.0 / returnPeriod;

  double probAtLeastOne = 1.0 - poissonProbability(0, lambda);
  double probExactlyOne = poissonProbability(1, lambda);

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "  Major Earthquakes (M >= 7.0): " << majorEvents << "\n";
  std::cout << "  Return Period: " << returnPeriod << " years\n";
  std::cout << "\n  Annual Probability (M >= 7.0):\n";
  std::cout << std::fixed << std::setprecision(4);
  std::cout << "    At least one event: " << (probAtLeastOne * 100) << "%\n";
  std::cout << "    Exactly one event:  " << (probExactlyOne * 100) << "%\n";
}

void displayCorrelationAnalysis(const std::vector<Earthquake> &data) {
  printHeader("CORRELATION ANALYSIS");

  std::vector<double> magnitudes, deaths, socio, injuries;
  for (const auto &eq : data) {
    magnitudes.push_back(eq.magnitude);
    deaths.push_back(static_cast<double>(eq.deaths));
    socio.push_back(static_cast<double>(eq.socioeconomicLevel));
    injuries.push_back(static_cast<double>(eq.injuries));
  }

  double corrMagDeaths = pearsonCorrelation(magnitudes, deaths);
  double corrMagInjuries = pearsonCorrelation(magnitudes, injuries);
  double corrSocioDeaths = pearsonCorrelation(socio, deaths);

  std::cout << std::fixed << std::setprecision(4);
  std::cout << "  Pearson Correlation Coefficients:\n\n";
  std::cout << "    Magnitude vs Deaths:        " << corrMagDeaths << "\n";
  std::cout << "    Magnitude vs Injuries:      " << corrMagInjuries << "\n";
  std::cout << "    Socioeconomic vs Deaths:    " << corrSocioDeaths << "\n";

  std::cout << "\n  Interpretation:\n";
  if (corrMagDeaths > 0.3) {
    std::cout
        << "    Moderate positive correlation between magnitude and deaths.\n";
  } else {
    std::cout
        << "    Weak correlation suggests other factors affect casualties.\n";
  }
}

void displayRegressionAnalysis(const std::vector<Earthquake> &data) {
  printHeader("TREND ANALYSIS (Linear Regression)");

  std::vector<double> years, magnitudes;
  for (const auto &eq : data) {
    if (eq.year > 0) {
      years.push_back(static_cast<double>(eq.year));
      magnitudes.push_back(eq.magnitude);
    }
  }

  double slope, intercept;
  linearRegression(years, magnitudes, slope, intercept);

  std::cout << std::fixed << std::setprecision(6);
  std::cout << "  Magnitude vs Year:\n";
  std::cout << "    Slope: " << slope << "\n";
  std::cout << "    Intercept: " << std::setprecision(2) << intercept << "\n";

  std::cout << "\n  Interpretation:\n";
  if (slope > 0.001) {
    std::cout
        << "    Slight upward trend in earthquake magnitudes over time.\n";
  } else if (slope < -0.001) {
    std::cout
        << "    Slight downward trend in earthquake magnitudes over time.\n";
  } else {
    std::cout << "    No significant temporal trend in magnitudes.\n";
  }
}

void displayRegionalAnalysis(const std::vector<Earthquake> &data) {
  printHeader("REGIONAL DISTRIBUTION");

  std::map<std::string, int> regionCounts = getRegionCounts(data);

  std::vector<std::pair<std::string, int>> sorted(regionCounts.begin(),
                                                  regionCounts.end());
  std::sort(sorted.begin(), sorted.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });

  std::cout << "  Earthquakes by Region:\n\n";
  for (const auto &pair : sorted) {
    std::cout << "    " << std::left << std::setw(22) << pair.first << ": "
              << pair.second << " events\n";
  }

  int maxCount;
  std::string mostActive = getMostActiveRegion(data, maxCount);
  std::cout << "\n  Most Seismically Active: " << mostActive << " (" << maxCount
            << " events)\n";
}

void displayRiskClassification(const std::vector<Earthquake> &data) {
  printHeader("RISK CLASSIFICATION");

  int lowCount = 0, mediumCount = 0, highCount = 0;
  std::vector<std::pair<std::string, RiskTier>> regionalRisks;

  for (const auto &eq : data) {
    RiskTier tier = classifyRisk(eq);
    switch (tier) {
    case RiskTier::LOW:
      lowCount++;
      break;
    case RiskTier::MEDIUM:
      mediumCount++;
      break;
    case RiskTier::HIGH:
      highCount++;
      break;
    }
  }

  std::cout << "  Risk Distribution:\n\n";
  std::cout << "    LOW Risk Events:    " << lowCount << "\n";
  std::cout << "    MEDIUM Risk Events: " << mediumCount << "\n";
  std::cout << "    HIGH Risk Events:   " << highCount << "\n";

  std::cout << "\n  Risk Classification Criteria:\n";
  std::cout << "    Based on: Magnitude * (4 - Socioeconomic Level)\n";
  std::cout << "    LOW:    Score < 15\n";
  std::cout << "    MEDIUM: Score 15-25\n";
  std::cout << "    HIGH:   Score > 25\n";

  std::cout << "\n  High Risk Events:\n\n";
  for (const auto &eq : data) {
    if (classifyRisk(eq) == RiskTier::HIGH) {
      std::cout << "    " << eq.year << " | M" << eq.magnitude << " | "
                << eq.region << " | " << eq.deaths << " deaths\n";
    }
  }
}

void displayFullReport(const std::vector<Earthquake> &data) {
  displayBasicStats(data);
  displayGutenbergRichter(data);
  displayPoissonAnalysis(data);
  displayCorrelationAnalysis(data);
  displayRegressionAnalysis(data);
  displayRegionalAnalysis(data);
  displayRiskClassification(data);

  std::cout << "\n======================================================\n";
  std::cout << "   Analysis Complete\n";
  std::cout << "======================================================\n\n";
}
