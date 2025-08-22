#ifndef ML_INFERENCE_H
#define ML_INFERENCE_H

#include <Arduino.h>
#include "../sensors/sensor_manager.h"

// Edge Impulse inference result structure
struct MLResult {
  float confidence;           // Overall confidence (0.0 - 1.0)
  String classification;      // Detected pattern name
  float* classScores;        // Individual class scores
  int numClasses;            // Number of classes in model
  unsigned long timestamp;    // Inference timestamp
  bool valid;                // Result validity flag
};

// Pattern detection thresholds
struct MLConfig {
  float confidenceThreshold;     // Minimum confidence for valid detection
  float criticalThreshold;       // Threshold for critical pattern alert
  int windowSize;               // Data window size for inference (samples)
  int windowOverlap;            // Window overlap (samples)
  bool enablePreprocessing;     // Enable data preprocessing
  float noiseThreshold;         // Noise level threshold
};

// Data preprocessing for ML input
class DataPreprocessor {
private:
  float* filterBuffer;
  int bufferSize;
  bool initialized;
  
public:
  DataPreprocessor(int size);
  ~DataPreprocessor();
  
  bool initialize();
  bool preprocessData(SensorData* rawData, int dataSize, float* output);
  bool applyFilter(float* data, int size, float cutoffFreq);
  bool normalizeData(float* data, int size);
  bool extractFeatures(float* data, int size, float* features);
};

class MLInference {
private:
  MLConfig config;
  DataPreprocessor* preprocessor;
  
  // Model state
  bool modelLoaded;
  bool initialized;
  
  // Inference buffer and timing
  float* inferenceBuffer;
  int bufferSize;
  unsigned long lastInferenceTime;
  unsigned long inferenceCount;
  unsigned long errorCount;
  
  // Results history for smoothing
  static const int RESULT_HISTORY_SIZE = 5;
  MLResult resultHistory[RESULT_HISTORY_SIZE];
  int historyIndex;
  bool historyFull;

public:
  MLInference();
  ~MLInference();
  
  // Initialization and setup
  bool initialize();
  bool loadModel();  // Load Edge Impulse model
  bool isInitialized() const { return initialized; }
  bool isModelLoaded() const { return modelLoaded; }
  
  // Configuration
  void setConfig(const MLConfig& newConfig);
  MLConfig getConfig() const { return config; }
  void setDefaultConfig();
  
  // Inference operations
  bool runInference(SensorData* sensorData, int dataSize, MLResult& result);
  bool preprocessSensorData(SensorData* rawData, int dataSize, float* processedData);
  
  // Result processing
  MLResult getSmoothedResult();  // Get smoothed result from history
  bool isPatternCritical(const MLResult& result);
  bool isResultReliable(const MLResult& result);
  
  // Pattern detection callbacks
  typedef void (*PatternCallback)(const MLResult& result, void* userData);
  void setPatternCallback(PatternCallback callback, void* userData);
  
  // Statistics and diagnostics
  void printModelInfo();
  void printInferenceStats();
  unsigned long getInferenceCount() const { return inferenceCount; }
  unsigned long getErrorCount() const { return errorCount; }
  float getAverageInferenceTime() const;
  
  // Edge Impulse specific methods (to be implemented with actual EI library)
  bool ei_classify(float* features, int featuresSize, float* result, int resultSize);
  int ei_get_classifier_frequency();
  size_t ei_get_classifier_dsp_input_length();
  
private:
  // Internal helper methods
  bool validateSensorData(SensorData* data, int size);
  void updateResultHistory(const MLResult& result);
  float calculateConfidenceScore(float* classScores, int numClasses);
  String getTopClassification(float* classScores, int numClasses);
};

// Global inference instance (if needed)
extern MLInference* g_mlInference;

#endif // ML_INFERENCE_H
