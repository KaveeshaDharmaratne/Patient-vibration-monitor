# Patient Vibration Monitor

## Overview
A real-time vibration monitoring system for patients using ESP32-S3 Nano, MPU6050 sensor, and Edge Impulse machine learning for pattern recognition. The system detects critical vibration patterns (such as seizures) and triggers appropriate alerts through multiple channels.

## Hardware Components
- **ESP32-S3 Nano**: Main microcontroller with WiFi and Bluetooth
- **MPU6050**: 6-axis accelerometer and gyroscope sensor
- **Buzzer**: Audio alert system
- **Status LEDs**: Visual indicators (RGB or multiple single-color LEDs)
- **Optional**: External speaker for enhanced audio alerts

## Features
- Real-time vibration pattern detection using Edge Impulse ML models
- Multi-modal alerts (audio, visual, remote)
- MQTT communication for remote monitoring
- WiFi connectivity with secure communication
- Sensor calibration and data logging
- Over-the-air configuration updates

## Project Structure
```
├── src/
│   ├── main.cpp              # Main application entry point
│   ├── sensors/              # MPU6050 and sensor management
│   ├── ml/                   # Edge Impulse ML inference
│   ├── alerts/               # Alert management (buzzer, LED, MQTT)
│   ├── communications/       # WiFi, MQTT, HTTP communication
│   └── config/               # Configuration management
├── data/                     # Sample data, calibration, logs
├── docs/                     # Documentation
├── include/                  # Header files
├── lib/                      # Local libraries
└── test/                     # Test files
```

## Quick Start
1. Clone this repository
2. Install PlatformIO
3. Connect hardware components according to pin configuration
4. Build and upload: `pio run -t upload`
5. Monitor serial output: `pio device monitor`

## Development Status
🚧 **In Development** - Initial project structure created on 2025-08-22

## Next Steps
1. Implement MPU6050 sensor integration
2. Create Edge Impulse model training pipeline
3. Develop alert system
4. Implement MQTT communication
5. Add configuration management
6. Clinical validation and testing

## License
[To be determined - consider medical device regulatory requirements]

## Contributing
Please see `docs/` directory for development guidelines and architecture documentation.

## Medical Disclaimer
This device is under development and not intended for medical diagnosis or treatment. Always consult healthcare professionals for medical decisions.
