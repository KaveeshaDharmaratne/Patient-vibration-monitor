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

## Planned Files
- `mpu6050_sensor.h/.cpp`: MPU6050 sensor driver and interface
- `sensor_manager.h/.cpp`: Main sensor management class
- `sensor_calibration.h/.cpp`: Sensor calibration routines

## Dependencies
- Adafruit MPU6050 library
- Wire library for I2C communication
- Adafruit Unified Sensor library

## Configuration
- I2C pins: SDA (GPIO21), SCL (GPIO22) - default for ESP32-S3
- Sampling rate: 100Hz for vibration pattern detection
- Range: ±2g for accelerometer, ±250°/s for gyroscope
