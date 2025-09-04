#include "alert_manager.h"

AlertManager::AlertManager() :
    lastButtonState(HIGH),
    lastDebounceTime(0),
    buzzerActive(false),
    buzzerStartTime(0) {
}

AlertManager::~AlertManager() {
    // Turn off buzzer when destroying
    digitalWrite(BUZZER_PIN, LOW);
}

bool AlertManager::initialize() {
    // Initialize buzzer pin
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    // Initialize alert button pin (A1) with external pull-up resistor
    pinMode(ALERT_BUTTON_PIN, INPUT);

    Serial.println("Alert Manager initialized - Button A1 (external pull-up), Buzzer A2");
    return true;
}

void AlertManager::update() {
    // Check for button press
    checkButtonPress();

    // Handle buzzer timing
    updateBuzzer();
}

void AlertManager::checkButtonPress() {
    // Read the button state
    bool reading = digitalRead(ALERT_BUTTON_PIN);

    // Check if button state changed
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    // If state has been stable for debounce delay
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        // If button was pressed (transition from HIGH to LOW)
        if (reading == BUTTON_PRESSED && lastButtonState == HIGH) {
            Serial.println("Button pressed on A1 - Buzzer ON for 1 second");
            // Set buzzer HIGH for 1 second
            digitalWrite(BUZZER_PIN, HIGH);
            buzzerActive = true;
            buzzerStartTime = millis();
        }
    }

    lastButtonState = reading;
}

void AlertManager::updateBuzzer() {
    if (buzzerActive) {
        unsigned long currentTime = millis();
        // Check if 1 second has passed
        if (currentTime - buzzerStartTime >= 1000) {
            // Turn off buzzer
            digitalWrite(BUZZER_PIN, LOW);
            buzzerActive = false;
            Serial.println("Buzzer OFF - 1 second completed");
        }
    }
}

void AlertManager::triggerManualAlert() {
    // Simple trigger for testing
    if (!buzzerActive) {
        digitalWrite(BUZZER_PIN, HIGH);
        buzzerActive = true;
        buzzerStartTime = millis();
        Serial.println("Manual alert triggered - Buzzer ON");
    }
}


