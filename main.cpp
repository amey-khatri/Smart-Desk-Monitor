#include <Arduino.h>
#include <pins.hpp>

#include <display.hpp> //Setup for display and timer functions
#include <ultrasonic.hpp> // Externs isInRange bool variable, setup for ultrasonic sensor and leds
#include <buzzer.hpp> //Setup for buzzer and buzzer functions
#include <mpu.hpp> //Setup for button and MPU 



TaskHandle_t timeElapsedTaskHandle = NULL;
TaskHandle_t get_MPU_dataTaskHandle = NULL;
TaskHandle_t trackSlouchTaskHandle = NULL;


void setup() {
  Serial.begin(115200);
  Wire.begin(MY_SDA, MY_SCL);

  setupUltrasonic(); // Includes LEDs
  setupDisplay();
  setupTimers();
  setupBuzzer();
  setupMPU(); // Includes button

  xTaskCreate(readUltrasonic, "Read Ultrasonic", 1000, NULL, 1, NULL);
  
}

void loop() {
  if (isInRange == true && wasInRange == false) { // Create/start functions
    xTaskCreate(timeElapsed, "Time Elapsed", 2048, NULL, 1, &timeElapsedTaskHandle);
    xTimerStart(drinkTimerHandle, 0);
    xTimerStart(standTimerHandle, 0);

    xTaskCreate(get_MPU_data, "Accelerometer", 3000, NULL, 1, &get_MPU_dataTaskHandle);
    xTaskCreate(trackSlouch, "Slouch Tracking", 3000, NULL, 1, &trackSlouchTaskHandle);


    wasInRange = true;
  } else if (isInRange == false && wasInRange == true) { // Delete/stop functions
    vTaskDelete(timeElapsedTaskHandle);
    xTimerStop(drinkTimerHandle, 0);
    xTimerStop(standTimerHandle, 0);

    vTaskDelete(get_MPU_dataTaskHandle);
    vTaskDelete(trackSlouchTaskHandle);



    display.clearDisplay();
    display.display();
    wasInRange = false;
  }

}







 