#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"

// MPU6050 sensor instance
Adafruit_MPU6050 mpu;

// Timing variables for precise sampling
unsigned long lastSampleTime = 0;
const unsigned long SAMPLE_INTERVAL_US = 10000; // 100Hz sampling (10ms = 10,000 microseconds)

// Calibration variables
float accel_offset_x = 0.0, accel_offset_y = 0.0, accel_offset_z = 0.0;
float gyro_offset_x = 0.0, gyro_offset_y = 0.0, gyro_offset_z = 0.0;
const int CALIBRATION_SAMPLES = 1000;

void calibrateSensor() {
  float accel_sum_x = 0, accel_sum_y = 0, accel_sum_z = 0;
  float gyro_sum_x = 0, gyro_sum_y = 0, gyro_sum_z = 0;
  
  // Collect calibration samples
  for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);
    
    accel_sum_x += accel.acceleration.x;
    accel_sum_y += accel.acceleration.y;
    accel_sum_z += accel.acceleration.z;
    
    gyro_sum_x += gyro.gyro.x;
    gyro_sum_y += gyro.gyro.y;
    gyro_sum_z += gyro.gyro.z;
    
    delay(5); // 5ms delay between calibration samples
  }
  
  // Calculate offsets (average of all samples)
  accel_offset_x = accel_sum_x / CALIBRATION_SAMPLES;
  accel_offset_y = accel_sum_y / CALIBRATION_SAMPLES;
  accel_offset_z = (accel_sum_z / CALIBRATION_SAMPLES) - 9.81; // Remove gravity from Z-axis
  
  gyro_offset_x = gyro_sum_x / CALIBRATION_SAMPLES;
  gyro_offset_y = gyro_sum_y / CALIBRATION_SAMPLES;
  gyro_offset_z = gyro_sum_z / CALIBRATION_SAMPLES;
}

void collectSample() {
  sensors_event_t accel, gyro, temp;
  
  // Get sensor readings
  mpu.getEvent(&accel, &gyro, &temp);
  
  // Apply calibration offsets
  float ax = accel.acceleration.x - accel_offset_x;
  float ay = accel.acceleration.y - accel_offset_y;
  float az = accel.acceleration.z - accel_offset_z;
  
  float gx = gyro.gyro.x - gyro_offset_x;
  float gy = gyro.gyro.y - gyro_offset_y;
  float gz = gyro.gyro.z - gyro_offset_z;
  
  // Output data in Edge Impulse CSV format (comma-separated)
  Serial.print(ax, 4);
  Serial.print(",");
  Serial.print(ay, 4);
  Serial.print(",");
  Serial.print(az, 4);
  Serial.print(",");
  Serial.print(gx, 4);
  Serial.print(",");
  Serial.print(gy, 4);
  Serial.print(",");
  Serial.println(gz, 4);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // Wait for serial port to connect
  }
  
  // Initialize I2C with optimized settings for ESP32 S3
  Wire.begin(); // SDA=11, SCL=12 for ESP32 S3 Nano
  Wire.setClock(400000); // 400kHz I2C clock for faster communication
  
  // Initialize MPU6050
  if (!mpu.begin(0x68, &Wire)) {
    while (1) {
      delay(1000);
    }
  }
  
  // Configure MPU6050 for optimal vibration detection
  // Accelerometer: ±4G range for hand vibration (more sensitive than ±8G)
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  
  // Gyroscope: ±500°/s range (suitable for hand movements)
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  
  // Digital Low Pass Filter: 94Hz bandwidth for vibration frequencies
  // This allows detection of tremor frequencies (4-12 Hz) while filtering noise
  mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);
  
  // Perform sensor calibration
  delay(2000);
  calibrateSensor();
  
  // Start data collection automatically
  lastSampleTime = micros();
  Serial.println("ax,ay,az,gx,gy,gz"); // CSV header for Edge Impulse
}

void loop() {
  unsigned long currentTime = micros();
  
  // Check if it's time for the next sample
  // if (currentTime - lastSampleTime >= SAMPLE_INTERVAL_US) {
    collectSample();
  //   lastSampleTime = currentTime;
  // }
  
  // Small delay to prevent watchdog timeout
  delayMicroseconds(100);
}



