#include "receiver.h"


Receiver rx1 = Receiver(2, 3, 4);
Receiver rx2 = Receiver(2, 3, 5);
Receiver rx3 = Receiver(2, 3, 6);
Receiver rx4 = Receiver(2, 3, 7);


void setup() {
    // Wait for modules to settle.
    delay(2000);

    // Set to race frequencies.
    rx1.setFrequency(5805);
    delay(500);
    rx2.setFrequency(5745);
    delay(500);
    rx3.setFrequency(5885);
    delay(500);
    rx4.setFrequency(5945);
}

void loop() {
    // Flash the LED.
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
