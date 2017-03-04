#ifndef RECEIVER_H
#define RECEIVER_H


#include <stdint.h>
#include "receiver_driver.h"


class Receiver {
    public:
        Receiver(
            uint8_t spiClockPin,
            uint8_t spiDataPin,
            uint8_t spiSelectPin
        );

        void setFrequency(uint16_t frequency);

    private:
        ReceiverDriver driver;
};


#endif
