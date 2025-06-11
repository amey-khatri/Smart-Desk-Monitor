#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <NewPing.h>
#include <pins.hpp>

#define MAX_DISTANCE 700 // Max rated 400-500 cm

extern NewPing sensor;
extern bool isInRange;
extern bool wasInRange;

void setupUltrasonic();
void readUltrasonic(void * parameters);


#endif