#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

// ESP32-S3 Nano Pin Configuration for Patient Vibration Monitor

// I2C Configuration for MPU6050
#define I2C_SDA_PIN         11
#define I2C_SCL_PIN         12
#define I2C_FREQUENCY       400000  // 400kHz

// Alert System Pins
#define BUZZER_PIN          25      // PWM capable pin for buzzer
#define LED_RED_PIN         26      // Red status LED
#define LED_GREEN_PIN       27      // Green status LED
#define LED_BLUE_PIN        14      // Blue status LED

// User Interface
#define BUTTON_PIN          0       // Built-in boot button
#define BUTTON_PRESSED      LOW

// MPU6050 Configuration
#define MPU6050_I2C_ADDR    0x68    // Default I2C address
#define ACCEL_RANGE         8       // ±8g
#define GYRO_RANGE          500     // ±500°/s

// System Configuration
#define SENSOR_SAMPLE_RATE  100     // 100Hz sensor sampling
#define ML_INFERENCE_RATE   1       // 1Hz ML inference
#define DATA_BUFFER_SIZE    200     // 2 seconds at 100Hz

// Power Management
#define ENABLE_PSRAM        true
#define ENABLE_POWER_SAVE   false

// Debug Configuration
#define DEBUG_SERIAL        true
#define DEBUG_SENSORS       true
#define DEBUG_ML            true
#define DEBUG_ALERTS        true

#endif // HARDWARE_CONFIG_H
