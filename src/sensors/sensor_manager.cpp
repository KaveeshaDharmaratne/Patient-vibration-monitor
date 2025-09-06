#include "sensor_manager.h"
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// MPU6050 sensor instance
Adafruit_MPU6050 mpu;

// Calibration variables
float accel_offset_x = 0.0, accel_offset_y = 0.0, accel_offset_z = 0.0;
const int CALIBRATION_SAMPLES = 1000;

// Timing variables for precise sampling
unsigned long lastSampleTime = 0;
const unsigned long SAMPLE_INTERVAL_US = 10000; // 100Hz sampling (10ms = 10,000 microseconds)

bool sensorInitialized = false;
bool sensorCalibrated = false;

// Edge Impulse buffer variables
float features[EI_CLASSIFIER_RAW_SAMPLE_COUNT * EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME];
int feature_index = 0;
bool buffer_full = false;

float ax = 0.0, ay = 0.0, az = 0.0;

SensorManager::SensorManager() :
    sensorInitialized(false),
    sensorCalibrated(false),
    feature_index(0),
    buffer_full(false) {}

SensorManager::~SensorManager() {
    // Cleanup if needed
}
float SensorManager::getAx() { return ax; }
float SensorManager::getAy() { return ay; }
float SensorManager::getAz() { return az; }

bool SensorManager::initialize() {
  // Initialize I2C with optimized settings for ESP32 S3
  Wire.begin(); // SDA=11, SCL=12 for ESP32 S3 Nano defaults
  Wire.setClock(400000); // 400kHz I2C clock for faster communication

  // Initialize MPU6050
  if (!mpu.begin(0x68, &Wire)) {
    sensorInitialized = false;
    return false;
  }

  // Configure MPU6050 for optimal vibration detection
  // Accelerometer: ±4G range for hand vibration (more sensitive than ±8G)
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);

  // Gyroscope: ±500°/s range (suitable for hand movements)
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // Digital Low Pass Filter: 94Hz bandwidth for vibration frequencies
  // This allows detection of tremor frequencies (4-12 Hz) while filtering noise
  mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);

  sensorInitialized = true;
  return true;
}

bool SensorManager::calibrate() {
  if (!sensorInitialized) {
    return false;
  }

  float accel_sum_x = 0, accel_sum_y = 0, accel_sum_z = 0;

  // Collect calibration samples
  for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);

    accel_sum_x += accel.acceleration.x;
    accel_sum_y += accel.acceleration.y;
    accel_sum_z += accel.acceleration.z;

    delay(5); // 5ms delay between calibration samples
  }

  // Calculate offsets (average of all samples)
  accel_offset_x = accel_sum_x / CALIBRATION_SAMPLES;
  accel_offset_y = accel_sum_y / CALIBRATION_SAMPLES;
  accel_offset_z = (accel_sum_z / CALIBRATION_SAMPLES) - 9.81; // Remove gravity from Z-axis

  sensorCalibrated = true;
  return true;
}

bool SensorManager::collectSample() {
  if (!sensorInitialized || !sensorCalibrated) {
    return false;
  }

  sensors_event_t accel, gyro, temp;

  // Get sensor readings
  mpu.getEvent(&accel, &gyro, &temp);

  // Apply calibration offsets
   ax = accel.acceleration.x - accel_offset_x;
   ay = accel.acceleration.y - accel_offset_y;
   az = accel.acceleration.z - accel_offset_z;

  // Store in features buffer for Edge Impulse inference
  if (feature_index < EI_CLASSIFIER_RAW_SAMPLE_COUNT) {
    features[feature_index * 3 + 0] = ax;
    features[feature_index * 3 + 1] = ay;
    features[feature_index * 3 + 2] = az;
    feature_index++;

    if (feature_index >= EI_CLASSIFIER_RAW_SAMPLE_COUNT) {
      buffer_full = true;
    }
  }

  // Output data in Edge Impulse CSV format (only during data collection phase)
  if (!buffer_full) {
    Serial.print(ax, 4);
    Serial.print(",");
    Serial.print(ay, 4);
    Serial.print(",");
    Serial.println(az, 4);
  }

  return true;
}

bool SensorManager::isReady() {
  return sensorInitialized && sensorCalibrated;
}

bool SensorManager::shouldCollectSample() {
  unsigned long currentTime = micros();

  if (currentTime - lastSampleTime >= SAMPLE_INTERVAL_US) {
    lastSampleTime = currentTime;
    return true;
  }

  return false;
}

// Edge Impulse integration methods
bool SensorManager::isBufferFull() {
  return buffer_full;
}

float* SensorManager::getFeatures() {
  return features;
}

void SensorManager::resetBuffer() {
  feature_index = 0;
  buffer_full = false;
}

int SensorManager::getFeatureCount() {
  return EI_CLASSIFIER_RAW_SAMPLE_COUNT * EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME;
}

