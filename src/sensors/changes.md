# Sensors Module Changes

## Overview
This directory contains sensor-related code for the Patient Vibration Monitor project.

## Components
- **MPU6050**: 6-axis accelerometer and gyroscope sensor
- **Sensor initialization and calibration routines**
- **Data acquisition and preprocessing**

## Changes Log

### 2025-08-22 - Initial Setup
- Created sensors directory structure
- Planned MPU6050 integration with I2C communication
- Designed sensor data structure for accelerometer and gyroscope readings

### 2025-09-03 - Refactoring and Implementation
- **Refactored main.cpp**: Moved all MPU6050 functionality from main.cpp to sensors folder
- **Created sensor_manager.cpp**: Implemented MPU6050 initialization, calibration, and data collection
- **Simplified sensor_manager.h**: Streamlined interface for current data collection phase
- **Updated hardware_config.h**: Fixed I2C pin definitions for ESP32-S3 Nano (GPIO 11, 12)
- **Clean separation**: Main application now only calls sensor manager methods

### 2025-09-04 - Edge Impulse Integration
- **Enhanced sensor_manager.h**: Added Edge Impulse integration methods
  - `isBufferFull()`: Check if inference buffer is ready
  - `getFeatures()`: Get features array for ML inference
  - `resetBuffer()`: Reset buffer for next inference window
  - `getFeatureCount()`: Get total number of features
- **Updated sensor_manager.cpp**: Implemented Edge Impulse buffer management
  - Added features buffer for 500 samples × 3 axes (1500 features)
  - Modified `collectSample()` to store data in inference buffer
  - Added buffer management for real-time inference
  - Maintained CSV output for data collection phase
- **Buffer Management**: Implemented circular buffer logic for continuous monitoring
- **Real-time Processing**: 100Hz sampling with 5-second inference windows

## Current Implementation
- **SensorManager class**: Handles all MPU6050 operations
- **100Hz sampling rate**: Optimized for vibration pattern detection
- **Automatic calibration**: Removes gravity and sensor offsets
- **CSV output format**: Compatible with Edge Impulse training
- **Error handling**: Proper initialization and calibration checks

## Planned Files
- `mpu6050_sensor.h/.cpp`: MPU6050 sensor driver and interface (future expansion)
- `sensor_manager.h/.cpp`: Main sensor management class ✅ IMPLEMENTED
- `sensor_calibration.h/.cpp`: Sensor calibration routines ✅ IMPLEMENTED
- `sensor_data_processor.h/.cpp`: Data preprocessing for ML (future)

## Dependencies
- Adafruit MPU6050 library ✅
- Wire library for I2C communication ✅
- Adafruit Unified Sensor library ✅

## Configuration
- I2C pins: SDA (GPIO8), SCL (GPIO9) - ESP32-S3 Nano defaults ✅
- Sampling rate: 100Hz for vibration pattern detection ✅
- Range: ±4g for accelerometer, ±500°/s for gyroscope ✅
- Filter: 94Hz bandwidth for tremor detection ✅
