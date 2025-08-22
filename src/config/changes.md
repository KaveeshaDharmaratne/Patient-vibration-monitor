# Configuration Module Changes

## Overview
This directory contains system configuration, constants, and settings management.

## Configuration Areas
- **Hardware Configuration**: Pin assignments, sensor settings
- **Network Configuration**: WiFi credentials, MQTT settings
- **ML Configuration**: Model parameters, thresholds
- **Alert Configuration**: Alert levels, timing, escalation

## Changes Log

### 2025-08-22 - Initial Setup
- Created config directory structure
- Planned centralized configuration management
- Designed secure credential storage
- Prepared for over-the-air configuration updates

## Planned Files
- `hardware_config.h`: GPIO pin assignments and hardware constants
- `network_config.h`: WiFi, MQTT, and communication settings
- `ml_config.h`: ML model parameters and classification thresholds
- `system_config.h`: General system settings and constants
- `config_manager.h/.cpp`: Configuration loading and management

## Configuration Management
- Use EEPROM/NVS for persistent storage
- JSON format for configuration files
- Secure storage for sensitive data (WiFi passwords, MQTT credentials)
- Factory reset capability
- Over-the-air configuration updates

## Hardware Pin Configuration (ESP32-S3 Nano)
- I2C SDA: GPIO21 (MPU6050)
- I2C SCL: GPIO22 (MPU6050)
- Buzzer: GPIO25 (PWM capable)
- Status LED Red: GPIO26
- Status LED Green: GPIO27
- Status LED Blue: GPIO14
- User Button: GPIO0 (built-in boot button)

## Network Configuration
- WiFi SSID and password storage
- MQTT broker settings (host, port, username, password)
- HTTP endpoints for data logging
- SSL certificates for secure communication

## Security Considerations
- Encrypt sensitive configuration data
- Use secure boot if available
- Implement configuration validation
- Audit trail for configuration changes
