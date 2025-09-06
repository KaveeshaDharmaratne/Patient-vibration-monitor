#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include <Arduino.h>
#include "../config/hardware_config.h"

class AlertManager {
private:
  // Button state tracking
  bool lastButtonState;
  unsigned long lastDebounceTime;
  const unsigned long DEBOUNCE_DELAY = 50; // 50ms debounce

  // Buzzer control
  bool buzzerActive;
  unsigned long buzzerStartTime;

public:
  AlertManager();
  ~AlertManager();

  // Initialization
  bool initialize();

  // Main update function - call in loop()
  void update();

  // Declare button press and buzzer update functions
  void updateBuzzer();
  void checkButtonPress();
  void triggerManualAlert();
};

#endif // ALERT_MANAGER_H
