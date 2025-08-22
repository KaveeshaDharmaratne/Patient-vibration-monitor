#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include <Arduino.h>
#include "../config/hardware_config.h"

// Alert types and severity levels
enum class AlertType {
  NONE,
  SYSTEM_STATUS,
  SENSOR_WARNING,
  PATTERN_DETECTED,
  CRITICAL_PATTERN
};

enum class AlertSeverity {
  INFO,      // Information only
  WARNING,   // Warning condition
  CRITICAL,  // Critical condition requiring immediate attention
  EMERGENCY  // Emergency condition
};

// Alert configuration structure
struct AlertConfig {
  bool enableBuzzer;
  bool enableLED;
  bool enableMQTT;
  
  int buzzerDuration;     // Duration in ms
  int buzzerFrequency;    // Frequency in Hz
  int repeatInterval;     // Repeat interval in ms
  int maxRepeats;         // Maximum number of repeats
  
  int ledBrightness;      // LED brightness (0-255)
  int ledFlashRate;       // Flash rate in ms
};

class AlertManager {
private:
  AlertConfig config;
  AlertType currentAlert;
  AlertSeverity currentSeverity;
  
  // Alert timing
  unsigned long alertStartTime;
  unsigned long lastAlertTime;
  int alertRepeatCount;
  bool alertActive;
  
  // Hardware control
  bool buzzerState;
  bool ledState;
  int currentLedBrightness;
  
  // Alert queue for multiple concurrent alerts
  static const int MAX_ALERT_QUEUE = 10;
  struct AlertItem {
    AlertType type;
    AlertSeverity severity;
    String message;
    unsigned long timestamp;
  };
  AlertItem alertQueue[MAX_ALERT_QUEUE];
  int queueHead, queueTail, queueSize;

public:
  AlertManager();
  ~AlertManager();
  
  // Initialization
  bool initialize();
  void setConfig(const AlertConfig& newConfig);
  AlertConfig getConfig() const { return config; }
  
  // Alert triggering
  void triggerAlert(AlertType type, AlertSeverity severity, const String& message = "");
  void clearAlert(AlertType type = AlertType::NONE);
  void clearAllAlerts();
  
  // Alert management
  void update();  // Call in main loop to handle alert timing
  bool isAlertActive() const { return alertActive; }
  AlertType getCurrentAlert() const { return currentAlert; }
  AlertSeverity getCurrentSeverity() const { return currentSeverity; }
  
  // Hardware control methods
  void setBuzzer(bool state, int frequency = 1000);
  void setLED(int red, int green, int blue);
  void setStatusLED(AlertSeverity severity);
  
  // Queue management
  bool addToQueue(AlertType type, AlertSeverity severity, const String& message);
  bool getNextAlert(AlertItem& item);
  void printQueue() const;
  
  // Pattern-specific alert methods
  void alertCriticalPattern(const String& patternName, float confidence);
  void alertSensorError(const String& sensorName, const String& error);
  void alertSystemStatus(const String& status);
  void alertNetworkStatus(bool connected);
  
  // Configuration helpers
  void setDefaultConfig();
  void enableQuietMode(bool enabled);
  void setEmergencyMode(bool enabled);
};

#endif // ALERT_MANAGER_H
