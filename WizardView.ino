#include <stdint.h>
#include "receiver.h"


#define PIN_LED 13
#define PIN_SPI_CLK 2
#define PIN_SPI_DATA 3
#define PIN_SPI_SS_RX1 4
#define PIN_SPI_SS_RX2 5
#define PIN_SPI_SS_RX3 6
#define PIN_SPI_SS_RX4 7

#define PIN_RSSI_RX1 A0
#define PIN_RSSI_RX2 A1
#define PIN_RSSI_RX3 A2
#define PIN_RSSI_RX4 A3

#define SERIAL_DELAY 25


Receiver rx1 = Receiver(
    PIN_SPI_CLK,
    PIN_SPI_DATA,
    PIN_SPI_SS_RX1,
    PIN_RSSI_RX1
);

Receiver rx2 = Receiver(
    PIN_SPI_CLK,
    PIN_SPI_DATA,
    PIN_SPI_SS_RX2,
    PIN_RSSI_RX2
);

Receiver rx3 = Receiver(
    PIN_SPI_CLK,
    PIN_SPI_DATA,
    PIN_SPI_SS_RX3,
    PIN_RSSI_RX3
);

Receiver rx4 = Receiver(
    PIN_SPI_CLK,
    PIN_SPI_DATA,
    PIN_SPI_SS_RX4,
    PIN_RSSI_RX4
);


void setup() {
    // Set pin defaults.
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_SPI_CLK, OUTPUT);
    pinMode(PIN_SPI_DATA, OUTPUT);
    pinMode(PIN_SPI_SS_RX1, OUTPUT);
    pinMode(PIN_SPI_SS_RX2, OUTPUT);
    pinMode(PIN_SPI_SS_RX3, OUTPUT);
    pinMode(PIN_SPI_SS_RX4, OUTPUT);
    pinMode(PIN_RSSI_RX1, INPUT);
    pinMode(PIN_RSSI_RX2, INPUT);
    pinMode(PIN_RSSI_RX3, INPUT);
    pinMode(PIN_RSSI_RX4, INPUT);

    digitalWrite(PIN_SPI_CLK, LOW);
    digitalWrite(PIN_SPI_DATA, LOW);
    digitalWrite(PIN_SPI_SS_RX1, HIGH);
    digitalWrite(PIN_SPI_SS_RX2, HIGH);
    digitalWrite(PIN_SPI_SS_RX3, HIGH);
    digitalWrite(PIN_SPI_SS_RX4, HIGH);

    // Set to race frequencies.
    delay(1000); // Wait for modules to settle.
    rx1.setFrequency(5805);
    rx2.setFrequency(5745);
    rx3.setFrequency(5885);
    rx4.setFrequency(5945);

    Serial.begin(115200);

    // Show that we're ready and on.
    digitalWrite(PIN_LED, HIGH);
}

void loop() {
    rx1.updateRssi();
    rx2.updateRssi();
    rx3.updateRssi();
    rx4.updateRssi();

    writeSerialData();
}


void writeSerialData() {
    static uint32_t nextSerialWrite = 0;
    if (millis() < nextSerialWrite)
        return;

    static const char seperator = '\t';

    Serial.print(rx1.rssi, DEC);
    Serial.print(seperator);
    Serial.print(rx2.rssi, DEC);
    Serial.print(seperator);
    Serial.print(rx3.rssi, DEC);
    Serial.print(seperator);
    Serial.print(rx4.rssi, DEC);
    Serial.println();

    nextSerialWrite = millis() + SERIAL_DELAY;
}
