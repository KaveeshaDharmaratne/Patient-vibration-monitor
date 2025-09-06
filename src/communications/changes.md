# Communications Module Changes

## Overview
This directory handles all communication protocols for the Patient Vibration Monitor.

## Communication Methods
- **MQTT**: For real-time alerts and data transmission
- **WiFi**: Primary connectivity method
- **HTTP/HTTPS**: For data logging and configuration updates

## Changes Log

### 2025-09-06 - MQTT Client Implementation
- Created `mqtt_client.h` and `mqtt_client.cpp` for MQTT communication using PubSubClient
- Implemented MQTTClient class with connect, publish, subscribe, loop, and callback methods
- Configured for Mosquitto broker (default port 1883, server configurable)

### 2025-09-06 - WiFi Manager Implementation
- Created communications directory structure
- Planned MQTT integration for critical alerts
- Designed WiFi connection management system
- Prepared for secure communication protocols

## Planned Files
- `http_client.h/.cpp`: HTTP client for data upload and configuration
- `communication_config.h`: Configuration constants and credentials

## Dependencies
- PubSubClient library for MQTT
- WiFi library (built-in ESP32)
- HTTPClient library (built-in ESP32)
- ArduinoJson for data serialization

## Configuration
- MQTT broker configuration (server, port, credentials)
- WiFi credentials management
- SSL/TLS certificates for secure communication
- Topic structure for different alert types
