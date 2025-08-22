#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "../config/hardware_config.h"

// Sensor data structure
struct SensorData {
  float accel_x, accel_y, accel_z;    // Accelerometer data (m/s²)
  float gyro_x, gyro_y, gyro_z;       // Gyroscope data (rad/s)
  float temperature;                   // Temperature (°C)
  unsigned long timestamp;             // Timestamp (ms)
};

// Circular buffer for sensor data
class SensorBuffer {
private:
  SensorData* buffer;
  int capacity;
  int size;
  int head;
  int tail;

public:
  SensorBuffer(int bufferSize);
  ~SensorBuffer();
  
  bool push(const SensorData& data);
  bool pop(SensorData& data);
  bool isFull() const;
  bool isEmpty() const;
  int getSize() const;
  SensorData* getBuffer() const;
  void clear();
};

class SensorManager {
private:
  Adafruit_MPU6050 mpu;
  SensorBuffer dataBuffer;
  bool initialized;
  bool calibrated;
  
  // Calibration offsets
  float accel_offset_x, accel_offset_y, accel_offset_z;
  float gyro_offset_x, gyro_offset_y, gyro_offset_z;
  
  // Status tracking
  unsigned long lastReadTime;
  unsigned long totalReadings;
  unsigned long errorCount;

public:
  SensorManager();
  ~SensorManager();
  
  // Initialization and setup
  bool initialize();
  bool calibrate(int samples = 1000);
  bool isInitialized() const { return initialized; }
  bool isCalibrated() const { return calibrated; }
  
  // Data acquisition
  bool readSensorData(SensorData& data);
  bool getLatestData(SensorData& data);
  SensorData* getDataBuffer() const;
  int getBufferSize() const;
  
  // Status and diagnostics
  void printStatus() const;
  void printCalibration() const;
  unsigned long getTotalReadings() const { return totalReadings; }
  unsigned long getErrorCount() const { return errorCount; }
  
  // Configuration
  bool setAccelRange(int range);  // 2, 4, 8, 16 g
  bool setGyroRange(int range);   // 250, 500, 1000, 2000 degrees/sec
  bool setSampleRate(int rate);   // Sample rate in Hz
};

#endif // SENSOR_MANAGER_H
