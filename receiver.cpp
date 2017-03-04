#include <stdint.h>
#include "receiver.h"


Receiver::Receiver(
    uint8_t spiClockPin,
    uint8_t spiDataPin,
    uint8_t spiSelectPin
) {
    this->driver.init(spiClockPin, spiDataPin, spiSelectPin);
}


void Receiver::setFrequency(uint16_t frequency) {
    uint16_t fLo = (frequency - 479) / 2;
    uint16_t regN = fLo / 32;
    uint16_t regA = fLo % 32;
    uint16_t synthRegB = (regN << 7) | regA;

    this->driver.setSynthRegisterB(synthRegB);
}



