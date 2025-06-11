#ifndef BUZZER_H
#define BUZZER_H

#include <pins.hpp>
#include <Arduino.h>

#define pwnChannel 0
#define pwnResolution 8
#define pwnFreq 3000

#define NOTE_C 262
#define NOTE_E 330
#define NOTE_G 392


void setupBuzzer();
void playSound();
void playSlouch();


#endif