#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

class DisplayManager {
private:
    Adafruit_SSD1306* display;
    int loadingProgress;
    bool wifiStatus;
    bool alertStatus;
    bool sensorStatus;
    bool communicationStatus;

    // Private helper methods
    void drawLoadingBar(int progress);
    void drawBattery(int percentage);
    void drawHeader();
    void drawSensorData(float ax, float ay, float az);
    void drawDateTime(const char* date, const char* time);
    void drawStatusIcons();
    
public:
    DisplayManager();
    ~DisplayManager();
    
    bool begin();
    void showLogo();
    void updateLoadingProgress(const char* status, int progress);
    void showMainScreen(float ax, float ay, float az, const char* date, const char* time, int batteryLevel);
    void updateBatteryLevel(int percentage);
    void updateSensorData(float ax, float ay, float az);
    void updateDateTime(const char* date, const char* time);
    
    // Status update methods
    void setWifiStatus(bool status);
    void setAlertStatus(bool status);
    void setSensorStatus(bool status);
    void setCommunicationStatus(bool status);
    
    // Direct access to display if needed
    Adafruit_SSD1306* getDisplay() { return display; }
};

#endif // DISPLAY_MANAGER_H
