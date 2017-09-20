#ifndef RECEIVER_DRIVER_H
#define RECEIVER_DRIVER_H


#include <stdint.h>


class ReceiverSpiDriver {
    public:
        void init(
            uint8_t spiClockPin,
            uint8_t spiDataPin,
            uint8_t spiSelectPin
        );

        void setSynthRegisterB(uint32_t data);


    private:
        uint8_t spiClockPin;
        uint8_t spiDataPin;
        uint8_t spiSelectPin;

        void sendBit(uint8_t value);
        void sendBits(uint32_t bits, uint8_t count);
        void sendSlaveSelect(uint8_t value);
        void sendRegister(uint8_t address, uint32_t data);
};


#endif
