#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>

// Edge Impulse model parameters (adjust based on your trained model)
// These should match your Edge Impulse project settings
#define EI_CLASSIFIER_RAW_SAMPLE_COUNT 500  // 5000ms @ 100Hz = 500 samples
#define EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME 3  // ax, ay, az

class SensorManager {

private:
  // Private members for internal state
  bool sensorInitialized;
  bool sensorCalibrated;

  // Edge Impulse data buffer
  float features[EI_CLASSIFIER_RAW_SAMPLE_COUNT * EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME];
  int feature_index;
  bool buffer_full;

public:
  SensorManager();
  ~SensorManager();

  // Core functionality
  bool initialize();              // Initialize MPU6050 sensor
  bool calibrate();               // Calibrate sensor offsets
  bool collectSample();           // Collect and output sensor data
  bool isReady();                 // Check if sensor is ready for data collection

  // Timing control
  bool shouldCollectSample();     // Check if it's time for next sample

  // Edge Impulse integration methods
  bool isBufferFull();            // Check if inference buffer is full
  float* getFeatures();           // Get features array for inference
  void resetBuffer();             // Reset buffer for next inference window
  int getFeatureCount();          // Get total number of features

};

#endif // SENSOR_MANAGER_H
