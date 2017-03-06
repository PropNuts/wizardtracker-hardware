#include <Arduino.h>
#include <stdint.h>

#include "receiver_driver.h"


#define SPI_ADDRESS_SYNTH_B 0x01


void ReceiverDriver::init(
    uint8_t spiClockPin,
    uint8_t spiDataPin,
    uint8_t spiSelectPin
) {
    this->spiClockPin = spiClockPin;
    this->spiDataPin = spiDataPin;
    this->spiSelectPin = spiSelectPin;
}

void ReceiverDriver::setSynthRegisterB(uint32_t data) {
    this->sendRegister(SPI_ADDRESS_SYNTH_B, data);
}


void ReceiverDriver::sendRegister(uint8_t address, uint32_t data) {
    this->sendSlaveSelect(LOW);

    this->sendBits(address, 4);
    this->sendBit(HIGH); // Enable write.

    this->sendBits(data, 20);

    // Finished clocking data in
    this->sendSlaveSelect(HIGH);
    digitalWrite(this->spiClockPin, LOW);
    digitalWrite(this->spiDataPin, LOW);
    delayMicroseconds(1);
}

void ReceiverDriver::sendBits(uint32_t bits, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        this->sendBit(bits & 0x1);
        bits >>= 1;
    }
}

void ReceiverDriver::sendBit(uint8_t value) {
    digitalWrite(this->spiClockPin, LOW);
    delayMicroseconds(1);

    digitalWrite(this->spiDataPin, value);
    delayMicroseconds(1);
    digitalWrite(this->spiClockPin, HIGH);
    delayMicroseconds(1);

    digitalWrite(this->spiClockPin, LOW);
    delayMicroseconds(1);
}

void ReceiverDriver::sendSlaveSelect(uint8_t value) {
    digitalWrite(this->spiSelectPin, value);
    delayMicroseconds(1);
}
