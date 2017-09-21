#include <Arduino.h>
#include <stdint.h>
#include "Monitor.h"


Monitor::Monitor(
    uint8_t pin,
    float multiplier
) {
    this->pin = pin;
    this->multiplier = multiplier;
}


void Monitor::update() {
    analogRead(this->pin); // Fake read to settle ADC
    this->value = (float) analogRead(this->pin) * this->multiplier;
}
