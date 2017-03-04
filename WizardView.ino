#include "receiver.h"


Receiver rx1 = Receiver(2, 3, 4);
Receiver rx2 = Receiver(2, 3, 5);
Receiver rx3 = Receiver(2, 3, 6);
Receiver rx4 = Receiver(2, 3, 7);


void setup() {
    // Wait for modules to settle.
    delay(1000);

    // Set to race frequencies.
    rx1.setFrequency(5665);
    rx2.setFrequency(5745);
    rx3.setFrequency(5885);
    rx4.setFrequency(5945);
}

void loop() {
    // Do nothing.
    delay(1000);
}
