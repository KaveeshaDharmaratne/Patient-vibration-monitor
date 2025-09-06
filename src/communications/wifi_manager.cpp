#include "wifi_manager.h"
#include <Arduino.h>

WiFiManager::WiFiManager(const char* ssid, const char* password) : _ssid(ssid), _password(password) {}

bool WiFiManager::connect() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);

    }
    return WiFi.status() == WL_CONNECTED;
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::disconnect() {
    WiFi.disconnect();
}

IPAddress WiFiManager::getIP() {
    return WiFi.localIP();
}
