#ifndef MPU_H
#define MPU_H

#include <pins.hpp>
#include <buzzer.hpp>

// Libraries for MPU
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <math.h>

extern Adafruit_MPU6050 mpu;

extern TaskHandle_t trackSlouchTaskHandle;

extern float zeroRoll;
extern float relativeRoll;
extern float roll;

extern unsigned long lastTime;

void get_MPU_data(void * parameters);
void trackSlouch(void * paramters);
void setupMPU();





#endif