#include <mpu.hpp>

Adafruit_MPU6050 mpu;

float zeroRoll = 0;
float relativeRoll = 0;
float roll = 0;

unsigned long lastTime = 0;

void get_MPU_data(void * parameters) {
  lastTime = millis();

  for (;;) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    unsigned long currentTime = millis();
    float dt = (currentTime - lastTime) / 1000.0f;  // Convert ms to seconds
    lastTime = currentTime;


    // Calculate roll from accelerometer (degrees)
    roll = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / M_PI;


    // Reset reference roll if button is pressed
    if (digitalRead(buttonPin) == LOW) {
      zeroRoll = roll;   // Set current roll as zero reference
      Serial.println("Zero set!");
      vTaskDelay(500 / portTICK_PERIOD_MS); // Debounce delay
    }

    relativeRoll = roll - zeroRoll;
    Serial.print("Relative Roll: ");
    Serial.println(relativeRoll);

    xTaskNotifyGive(trackSlouchTaskHandle);

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void trackSlouch(void * parameters) {
    for(;;) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
         
        if (relativeRoll > 15) {
            vTaskDelay(pdMS_TO_TICKS(5000));

            if (relativeRoll > 15) {

                while (relativeRoll > 15) {
                    playSlouch();
                    vTaskDelay(pdMS_TO_TICKS(1000));
                }
            }
        }
    }


}


void setupMPU() {
    Serial.begin(115200);

    Wire.begin(MY_SDA, MY_SCL);
    mpu.begin();

    mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    pinMode(buttonPin, INPUT);
}