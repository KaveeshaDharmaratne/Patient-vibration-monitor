#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"

// // Project includes (to be created)
// // #include "sensors/sensor_manager.h"
// // #include "ml/ml_inference.h"
// // #include "alerts/alert_manager.h"
// // #include "communications/wifi_manager.h"
// // #include "communications/mqtt_client.h"
// // #include "config/system_config.h"

Adafruit_MPU6050 mpu;
unsigned long timestamp;
unsigned long lastTimestamp;

void setup() {
  Serial.begin(115200);

  if(!mpu.begin()) {
    Serial.println("Sensor initialization failed");
    while(1)
      yield(); // Halt if sensor fails
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  

}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Serial.print("timeStamp\t");

  // Serial.print(millis());
  Serial.print(a.acceleration.x);
  Serial.print("\t");
  Serial.print(a.acceleration.y);
  Serial.print("\t");
  Serial.print(a.acceleration.z);
  Serial.print("\t");
  
  Serial.print(g.gyro.x);
  Serial.print("\t");
  Serial.print(g.gyro.y);
  Serial.print("\t");
  Serial.print(g.gyro.z);
  Serial.print("\n");


  delay(100);

}

// // System state
// bool systemInitialized = false;
// bool wifiConnected = false;
// bool sensorCalibrated = false;

// // Timing variables
// unsigned long lastSensorRead = 0;
// unsigned long lastMLInference = 0;
// const unsigned long SENSOR_INTERVAL = 10; // 100Hz sampling
// const unsigned long ML_INTERVAL = 1000;   // 1Hz inference

// void setup() {
//   Serial.begin(115200);
//   delay(1000);
  
//   Serial.println("=== Patient Vibration Monitor ===");
//   Serial.println("Initializing system...");
  
//   // Initialize I2C for MPU6050
//   Wire.begin();
  
//   // TODO: Initialize components
//   // 1. Load configuration
//   // 2. Initialize sensors (MPU6050)
//   // 3. Calibrate sensors
//   // 4. Initialize WiFi
//   // 5. Initialize MQTT client
//   // 6. Initialize alert system
//   // 7. Load ML model
  
//   Serial.println("System initialization completed");
//   systemInitialized = true;
// }

// void loop() {
//   if (!systemInitialized) {
//     delay(100);
//     return;
//   }
  
//   unsigned long currentTime = millis();
  
//   // Read sensors at high frequency (100Hz)
//   if (currentTime - lastSensorRead >= SENSOR_INTERVAL) {
//     // TODO: Read MPU6050 data
//     // - Read accelerometer and gyroscope
//     // - Store in data buffer for ML processing
//     // - Update sensor status
    
//     lastSensorRead = currentTime;
//   }
  
//   // Perform ML inference at lower frequency (1Hz)
//   if (currentTime - lastMLInference >= ML_INTERVAL) {
//     // TODO: ML inference
//     // - Prepare feature vector from sensor data buffer
//     // - Run Edge Impulse inference
//     // - Process classification results
//     // - Trigger alerts if critical pattern detected
    
//     lastMLInference = currentTime;
    
//     // Debug output
//     Serial.println("System running - ML inference cycle");
//   }
  
//   // TODO: Handle other tasks
//   // - Process MQTT messages
//   // - Update system status
//   // - Handle configuration updates
//   // - Manage alert states
  
//   // Small delay to prevent watchdog issues
//   delay(1);
// }