#ifndef MONITOR_H
#define MONITOR_H

#include <stdint.h>


class Monitor {
    public:
        Monitor(uint8_t pin, float multiplier);
        void update();

        float value;

    private:
        uint8_t pin;
        float multiplier;
};


#endif
