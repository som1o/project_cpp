# Seismic Intelligence Analysis

## Overview
By analyzing historical earthquake data, the system identifies patterns and estimates the likelihood of future seismic events. The goal is to turn complex geological data into clear,and actionable information.

## What This Tool Does

### 1. Analyzes Stress Buildup
The system looks at how often small earthquakes happen to predict the likelihood of big ones. In seismology, frequent small tremors often release energy safely. If the system sees *fewer* small quakes than expected, it warns that pressure might be building up underground—a potential signal for a larger future event.

### 2. Predicts Future Probabilities
Using established mathematical models, the tool calculates the specific odds of a major earthquake occurring within a certain timeframe. Instead of guessing, it uses history to answer questions like: *"How likely is a major earthquake in the next 20 years?"*

### 3. Risk & Vulnerability Assessment
Not all earthquakes cause the same damage. This tool calculates a "Risk Score" for past events by combining:
- **Magnitude**: How strong the shaking was.
- **Socioeconomic Vulnerability**: How well-built the infrastructure is in that area.
It categorizes events into **Low**, **Medium**, or **High** risk levels to help identify which communities are most in danger.

### 4. Interactive Casualty Prediction
The system uses a **Logistic Regression** machine learning model to predict if an earthquake will be deadly.
- It learns from historical data (Magnitude + Socioeconomic Vulnerability).
- It enables you to simulate scenarios: *"If a magnitude 7.0 hits a highly vulnerable area, will there be casualties?"*

### 5. Regional Hotspots
The system maps out which areas (like Chittagong, Sylhet, or Dhaka) are historically most active. This helps prioritize where to reinforce buildings and conduct safety drills.

### 6. Interactive Probability Calculator
You act as the researcher! The tool includes an interactive feature where you can input your own scenarios.
- You enter a **Magnitude** (e.g., 7.0).
- You enter a **Time Period** (e.g., 50 years).
- The system instantly calculates the statistical probability of such an earthquake happening based on the region's history.

## How to Use It

### Step 0: Build
Before running the tool, you need to compile it. Open your terminal in the project folder and paste:
```bash
```bash
g++ -o seismic_analysis main.cpp statistics.cpp LogisticRegression.cpp
```

### Step 1: Run
Launch the application from your computer's terminal.
```bash
./seismic_analysis
```

### Step 2: Read the Report
The program will display a comprehensive report covering:
- **Basic Statistics**: The largest, average, and total earthquakes recorded.
- **Stress Analysis**: Whether the fault lines are releasing stress normally or storing it up.
- **Correlation**: How earthquake size relates to historical damages and casualties.

### Step 3: Try Your Own Scenarios
At the very end, the program will ask you for input.
1. Type the earthquake magnitude you are worried about (e.g., `6.5`).
2. Type the number of years you want to forecast for (e.g., `10` or `100`).
The tool will show you the exact percentage chance of that event occurring.

### Step 4: ML Predictions
The program will also ask you to test the ML model:
1. Enter a Magnitude (e.g., `7.5`).
2. Enter a Vulnerability Level (1=Low, 3=High).
3. The model predicts the probability of casualties based on patterns it learned from history.

## Why This Matters
Bangladesh sits at a complex junction of three massive tectonic plates. Understanding these risks isn't just about numbers—it's about saving lives. By using data to better understand our geological history, we can take smarter steps today to prepare for tomorrow.

---
*Note: This tool uses statistical models based on available historical data (roughly 1548–2025). While it provides scientifically grounded estimates, earthquakes are complex natural phenomena and strictly determining their exact timing is currently impossible for any science.*
