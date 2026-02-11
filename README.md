# Earthquake Analysis & Safety Guide

A friendly C++ tool designed to help you understand local seismic history and look into the future through data.

## Features
- **Historical Analysis**: We look at how many earthquakes have happened, their average strength, and where they occurred most often.
- **Trend Spotting (Regression)**: By analyzing how earthquake sizes change over time, we can provide a **Safety Outlook** and even estimate potential earthquake intensity for future years.
- **Risk Calculator (Poisson)**: A tool to estimate the probability of a major event happening within your lifetime or a specific timeframe.

## How to Use

### Build
To get started, compile the files using:
```bash
g++ main.cpp function.cpp -o earthquake_analysis
```

### Run
Simply run the application and follow the interactive prompts:
```bash
./earthquake_analysis
```

## Behind the Scenes
The program carefully reads your `earthquakes.csv` file and uses mathematical models to turn raw numbers into meaningful safety insights.
