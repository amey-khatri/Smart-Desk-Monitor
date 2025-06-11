#ifndef DISPLAY_H
#define DISPLAY_H

#include <pins.hpp>

#include <buzzer.hpp>

// Libraries needed for OLED display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

extern Adafruit_SSD1306 display;

void setupDisplay();
void timeElapsed(void * parameters);

extern TimerHandle_t clearTimerHandle;
extern TimerHandle_t drinkTimerHandle;
extern TimerHandle_t standTimerHandle;

void clearScreenCallback (TimerHandle_t xtimer);
void drinkTimerCallback (TimerHandle_t xtimer);
void standTimerCallback (TimerHandle_t xtimer);
void setupTimers();



#endif
