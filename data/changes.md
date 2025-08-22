# Data Directory Changes

## Overview
This directory contains sample data, calibration files, and temporary storage for the Patient Vibration Monitor.

## Data Types
- **Sample Data**: Training data for Edge Impulse model development
- **Calibration Data**: Sensor calibration coefficients and offsets
- **Log Files**: System logs and debug information
- **Configuration Backups**: Backup configuration files

## Changes Log

### 2025-08-22 - Initial Setup
- Created data directory structure
- Prepared for sample vibration data collection
- Planned calibration data storage
- Set up logging infrastructure

## Planned Files and Subdirectories
- `samples/`: Raw vibration data samples for ML training
  - `normal/`: Normal movement patterns
  - `critical/`: Critical vibration patterns (seizures, falls)
  - `artifacts/`: Movement artifacts and noise samples
- `calibration/`: Sensor calibration files
  - `mpu6050_calibration.json`: MPU6050 calibration coefficients
- `logs/`: System log files
  - `system.log`: General system logs
  - `sensor.log`: Sensor data logs
  - `ml.log`: ML inference logs
- `config_backup/`: Configuration backup files

## Data Collection Guidelines
1. **Sample Collection**:
   - Collect at least 10 minutes of each pattern type
   - Include various patient positions and orientations
   - Record environmental conditions and patient information
   - Ensure patient privacy and data anonymization

2. **Data Format**:
   - CSV format for raw sensor data
   - JSON format for metadata and configuration
   - Timestamp all data points
   - Include sensor calibration state

3. **Privacy and Security**:
   - No personally identifiable information in raw data
   - Use patient ID codes instead of names
   - Encrypt sensitive data files
   - Regular data cleanup and archival

## Data Management
- Implement data rotation for log files
- Automatic cleanup of old temporary files
- Secure data transmission for remote storage
- Data validation and integrity checks
