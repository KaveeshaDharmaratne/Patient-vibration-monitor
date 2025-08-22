# Machine Learning Module Changes

## Overview
This directory contains Edge Impulse integration and ML inference code for vibration pattern recognition.

## ML Components
- **Edge Impulse Model**: Trained model for vibration pattern classification
- **Inference Engine**: Real-time pattern recognition
- **Feature Extraction**: Signal processing for ML input preparation

## Changes Log

### 2025-08-22 - Initial Setup
- Created ML directory structure
- Planned Edge Impulse C++ library integration
- Designed inference pipeline for real-time pattern detection
- Prepared data preprocessing for ML model input

## Planned Files
- `edge_impulse_inferencing.h`: Edge Impulse generated header
- `ml_inference.h/.cpp`: Main inference engine
- `feature_extraction.h/.cpp`: Signal preprocessing and feature extraction
- `pattern_classifier.h/.cpp`: Pattern classification and threshold management

## Edge Impulse Integration
1. Train model on Edge Impulse platform with vibration data
2. Export C++ library for ESP32
3. Integrate inference code with sensor data pipeline
4. Implement real-time classification

## Model Requirements
- Input: Accelerometer and gyroscope data windows (e.g., 2-second windows)
- Output: Classification probabilities for different vibration patterns
- Target patterns: Normal, Critical, Seizure, Movement, etc.
- Inference frequency: Real-time (every 100ms-1s)

## Performance Considerations
- Use PSRAM for model storage and intermediate calculations
- Optimize inference speed for real-time operation
- Implement confidence thresholds for reliable detection
