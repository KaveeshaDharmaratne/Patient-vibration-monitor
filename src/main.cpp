#include <Arduino.h>
#include "sensors/sensor_manager.h"
#include "alerts/alert_manager.h"
#include "display/display_manager.h"



// Edge Impulse SDK includes (these will be available after you add the SDK)
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"

//FreeRtos handles
TaskHandle_t TaskDisplay;
TaskHandle_t TaskInit;

//Shared Memories
volatile int progress = 0;
volatile int step = 0;



// Create sensor manager instance
SensorManager sensorManager;

// Create alert manager instance
AlertManager alertManager;
DisplayManager displayManager; // Create display manager instance

void serialComInit(){
 while (!Serial) {
    vTaskDelay(10/portTICK_PERIOD_MS);// Wait for serial port to connect
    Serial.println("Waiting for Serial connection...");
  }
}
void sensorInit(){
// Initialize the sensor
  if (!sensorManager.initialize()) {
    Serial.println("MPU6050 initialization failed!");
    while (1) {
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }
}
void alertManagerInit(){
    if (!alertManager.initialize()) {
    Serial.println("Alert manager initialization failed!");
    while (1) {
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }
}

void sensorCalibration(){
  vTaskDelay(2000/portTICK_PERIOD_MS); // Give sensor time to stabilize
  Serial.println("Calibrating sensor...");

  if (!sensorManager.calibrate()) {
    Serial.println("Calibration failed!");
    while (1) {
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }
  Serial.println("Calibration complete!");
}
void InitTask(void *pvParameters){
  vTaskDelay(3000 / portTICK_PERIOD_MS); // small wait

  step = 1;
  sensorInit();
  progress = 25;

  step = 2;
  alertManagerInit();
  progress = 50;

  step = 3;
  sensorCalibration();
  progress = 75;

  
  serialComInit();
  step = 4;
  vTaskDelay(500 / portTICK_PERIOD_MS);
  progress = 100;
  
  vTaskDelete(NULL); // done
}

void DisplayTask(void *pvParameters){
  displayManager.begin();
  //show the logo on display for 2000ms 
  displayManager.showLogo();
  displayManager.getDisplay()->clearDisplay();

  displayManager.getDisplay()->setCursor(0,16);
  
  while (1) {
    if(step<5){
    displayManager.getDisplay()->clearDisplay();
    displayManager.getDisplay()->setTextSize(1);
    displayManager.getDisplay()->setCursor(0, 0);
    displayManager.getDisplay()->println("Initializing...");
   
    // Show step text
    displayManager.getDisplay()->setCursor(0, 16);
    }
    switch(step) {
      case 0: displayManager.getDisplay()->println("Starting..."); break;
      case 1: displayManager.getDisplay()->println("Alert Manager..."); break;
      case 2: displayManager.getDisplay()->println("Sensor Calibration..."); break;
      case 3: displayManager.getDisplay()->println("Sensor Intialization..."); break;
      case 4: displayManager.getDisplay()->println("Serial Communication Done!"); 
             
           vTaskDelay(3000 / portTICK_PERIOD_MS);
           step = 5;
           displayManager.showMainScreen(sensorManager.getAx(),sensorManager.getAy(),sensorManager.getAz(),
"00-00-0000","00:00:00",100);    
            break;
      case 5: displayManager.updateSensorData(sensorManager.getAx(),sensorManager.getAy(),sensorManager.getAz()); break;

    }
    if(step<5){
    // Draw progress bar
    displayManager.getDisplay()->drawRect(10, 50, 100, 8, SSD1306_WHITE);
    displayManager.getDisplay()->fillRect(10, 50, progress, 8, SSD1306_WHITE);
    displayManager.getDisplay()->display();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }
   // should never reach here
}

// Anomaly detection threshold (adjust based on your model training)
// Typical range: 0.3 - 0.8, start with 0.5
const float ANOMALY_THRESHOLD = 0.5;
/*
void loadingBar() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 45);
  display.println("Loading...");
  display.drawRoundRect(10, 57, 108, 5, 2, WHITE);
  for (int i = 0; i <= 108; i++) {
    display.fillRoundRect(10, 57, i, 5, 2, WHITE);
    display.display();
    delay(20);
  }
}
  */
#define buzzerPin A2

void setup() {
  pinMode(buzzerPin,OUTPUT);
  digitalWrite(buzzerPin,LOW);
  Serial.begin(115200);
  displayManager.begin();

  Serial.println("=== Patient Vibration Monitor with ML ===");
  /*
  // Show logo
  displayManager.showLogo();
  sensorInit();
  sensorCalibration();  // Perform sensor calibration
  alertManagerInit();  // Initialize the alert manager
  serialComInit();
*/
  // Show loading bar
  
  xTaskCreatePinnedToCore(DisplayTask,"display",4096,NULL,1,&TaskDisplay,0);
  xTaskCreatePinnedToCore(InitTask,"Init",4096,NULL,1,&TaskInit,0);

  Serial.println("Initializing Edge Impulse SDK...");
  Serial.println("Starting vibration monitoring...");
  Serial.println("ax,ay,az"); // CSV header for Edge Impulse data collection
  displayManager.showMainScreen(sensorManager.getAx(),sensorManager.getAy(),sensorManager.getAz(),"00-00-0000","00:00:00",100);
}

void loop() {
  // Check if it's time to collect a sample

  if (sensorManager.shouldCollectSample()) {
    sensorManager.collectSample();

    // Update display with latest sensor data
    //displayManager.updateSensorData(sensorManager.getAx(),sensorManager.getAy(),sensorManager.getAz());
    // Placeholder values
    // Check if we have enough data for inference
    if (sensorManager.isBufferFull()) {
      Serial.println("\n--- Running Edge Impulse Inference ---");

      // Prepare signal for inference
      signal_t signal;
      numpy::signal_from_buffer(sensorManager.getFeatures(),
                              EI_CLASSIFIER_RAW_SAMPLE_COUNT * EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME,
                              &signal);  

      // Run classifier
      ei_impulse_result_t result = {0};
      EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

      if (res != EI_IMPULSE_OK) {
        Serial.println("Edge Impulse inference failed!");
      } else {
        // Print anomaly score
        float anomaly_score = result.anomaly;
        Serial.print("Anomaly Score: ");
        Serial.println(anomaly_score, 4);

        // Check for abnormal patterns
        if (anomaly_score > ANOMALY_THRESHOLD) {
          // Anomaly detected - trigger alert
          Serial.println("ALERT: Abnormal vibration pattern detected!");
          // Note: Alert triggering removed in simplified version
          // alertManager.triggerAlert(AlertType::ANOMALY_DETECTED, anomaly_score);
        } else {
          Serial.println("✓ Normal vibration pattern");
        }

        // Print classification results for all labels
        Serial.println("Classification Results:");
        for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
          Serial.print("  ");
          Serial.print(result.classification[i].label);
          Serial.print(": ");
          Serial.println(result.classification[i].value, 4);
        }
      }

      // Reset buffer for next inference window
      sensorManager.resetBuffer();
      Serial.println("--- Buffer reset, continuing monitoring ---\n");
    }
  }

  // Update alert manager (handles button press detection and buzzer timing)
  alertManager.update();

  // Small delay to prevent watchdog timeout
  delayMicroseconds(100);
}




