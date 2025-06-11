// Includes code for ultrasonic sensor and led setup


#include <ultrasonic.hpp>

NewPing sensor(trigPin, echoPin, MAX_DISTANCE);

// Used to determine when to start functions
bool isInRange = false;
bool wasInRange = false;



void setupUltrasonic() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(ledGreen, OUTPUT);
    pinMode(ledRed, OUTPUT);

    // Serial.begin(115200);
}

void readUltrasonic(void * parameters) {
    for(;;) {
        unsigned long distance = sensor.ping_cm();
        //Serial.println(distance);

        if (distance < 80) {
            digitalWrite(ledGreen, HIGH);
            digitalWrite(ledRed, LOW);
            if (! isInRange) {
                isInRange = true;
            }
        } else {
            digitalWrite(ledGreen, LOW);
            digitalWrite(ledRed, HIGH);

            isInRange = false;
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}
