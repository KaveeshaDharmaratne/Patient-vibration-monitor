# Alerts Module Changes

## Overview
This directory handles all alert mechanisms for critical vibration pattern detection.

## Alert Types
- **Audio Alerts**: Buzzer/speaker for immediate local notification
- **Visual Alerts**: LED indicators for status and alerts
- **Remote Alerts**: MQTT messages for external notification systems

## Changes Log

### 2025-08-22 - Initial Setup
- Created alerts directory structure
- Planned multi-modal alert system (audio, visual, remote)
- Designed alert escalation based on pattern severity
- Prepared buzzer/LED integration

## Planned Files
- `alert_manager.h/.cpp`: Main alert coordination and management
- `buzzer_controller.h/.cpp`: Audio alert control (buzzer/speaker)
- `led_controller.h/.cpp`: Visual indicator management
- `alert_config.h`: Alert thresholds, timing, and escalation rules

## Alert Scenarios
1. **Critical Pattern Detected**:
   - Immediate buzzer activation
   - Red LED flashing
   - MQTT alert message with timestamp and severity
   
2. **System Status**:
   - Green LED for normal operation
   - Blue LED for WiFi connection status
   - Yellow LED for sensor warnings

3. **Alert Escalation**:
   - Initial alert: 3-second buzzer + LED
   - If not acknowledged: Repeat every 30 seconds
   - Remote notification via MQTT for all critical events

## Hardware Requirements
- Buzzer: GPIO pin for PWM control
- Status LEDs: RGB LED or multiple single-color LEDs
- Optional: External speaker for louder alerts

## Configuration
- Alert volume levels
- LED brightness settings
- Alert duration and repetition intervals
- MQTT topic structure for remote alerts
