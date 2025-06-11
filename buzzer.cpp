#include <buzzer.hpp>

void setupBuzzer() {
    ledcSetup(pwnChannel, pwnFreq, pwnResolution);
    ledcAttachPin(buzzerPin, pwnChannel);

    ledcWrite(pwnChannel, 10);
    ledcWriteTone(pwnChannel, 0);
    
}

void playSound() {
    int delaytime = 1000; 
    int volume = 10;

    ledcWriteTone(pwnChannel, NOTE_C);
    vTaskDelay(pdMS_TO_TICKS(delaytime));
    ledcWrite(pwnChannel, volume);

    ledcWriteTone(pwnChannel, NOTE_E);
    vTaskDelay(pdMS_TO_TICKS(delaytime));
    ledcWrite(pwnChannel, volume);
    
    ledcWriteTone(pwnChannel, NOTE_G);
    vTaskDelay(pdMS_TO_TICKS(delaytime));
    ledcWrite(pwnChannel, volume);

    ledcWriteTone(pwnChannel, 0);
}

void playSlouch() {
    ledcWriteTone(pwnChannel, 80);
    vTaskDelay(pdMS_TO_TICKS(1000));
    ledcWriteTone(pwnChannel, 0);
    
}
