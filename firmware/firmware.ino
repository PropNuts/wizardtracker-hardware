#include <stdint.h>

#include "Config.h"
#include "Receiver.h"
#include "Monitor.h"
#include "Timer.h"


Receiver receivers[RECEIVER_COUNT];

#ifdef TEMP_MONITORING_ENABLED
    Monitor tempMonitor(TEMP_MONITORING_PIN, TEMP_MONITORING_MULTIPLIER);
#endif

#ifdef VOLTAGE_MONITORING_ENABLED
    Monitor voltMonitor(VOLTAGE_MONITORING_PIN, VOLTAGE_MONITORING_MULTIPLIER);
#endif

Timer rssiTimer(RSSI_DELAY_MS);
#ifdef MONITORING_ENABLED
    Timer monitorTimer(MONITORING_DELAY_MS);
#endif


void setup() {
    // Set pin defaults.
    pinMode(LED_PIN, OUTPUT);
    pinMode(RECEIVER_PIN_SPI_CLK, OUTPUT);
    pinMode(RECEIVER_PIN_SPI_DATA, OUTPUT);

    digitalWrite(RECEIVER_PIN_SPI_CLK, LOW);
    digitalWrite(RECEIVER_PIN_SPI_DATA, LOW);

    for (uint8_t i = 0; i < RECEIVER_COUNT; i++) {
        pinMode(RECEIVER_PIN_SPI_SS_START - i, OUTPUT);
        pinMode(RECEIVER_PIN_RSSI_START + i, INPUT);
        digitalWrite(RECEIVER_PIN_SPI_SS_START + i, HIGH);
    }

    #ifdef TEMP_MONITORING_ENABLED
        pinMode(TEMP_MONITORING_PIN, INPUT);
    #endif

    #ifdef VOLTAGE_MONITORING_ENABLED
        pinMode(VOLTAGE_MONITORING_PIN, INPUT);
    #endif

    // Configure receivers.
    for (uint8_t i = 0; i < RECEIVER_COUNT; i++) {
        receivers[i].init(
            RECEIVER_PIN_SPI_CLK,
            RECEIVER_PIN_SPI_DATA,
            RECEIVER_PIN_SPI_SS_START - i,
            RECEIVER_PIN_RSSI_START + i
        );

        receivers[i].setFrequency(5695);
    }

    // Wait for modules to settle.
    delay(BOOT_DELAY_MS);

    // Get ready to go!
    rssiTimer.reset();
    #ifdef MONITORING_ENABLED
        monitorTimer.reset();
    #endif

    Serial.begin(SERIAL_BAUD);
    digitalWrite(LED_PIN, HIGH);
}

void loop() {
    if (rssiTimer.hasTicked()) {
        for (uint8_t i = 0; i < RECEIVER_COUNT; i++) {
            receivers[i].updateRssi();
        }

        writeRssiData();
        rssiTimer.reset();
    }

    #ifdef MONITORING_ENABLED
        if (monitorTimer.hasTicked()) {
            #ifdef TEMP_MONITORING_ENABLED
                tempMonitor.update();
                writeTempMonitorData();
            #endif

            #ifdef VOLTAGE_MONITORING_ENABLED
                voltMonitor.update();
                writeVoltMonitorData();
            #endif

            monitorTimer.reset();
        }
    #endif

    parseCommands();
}


void writeRssiData() {
    static const char* prefix = "r ";
    static const char seperator = ' ';

    Serial.print(prefix);

    for (uint8_t i = 0; i < RECEIVER_COUNT; i++) {
        Serial.print(receivers[i].rssi, DEC);

        if (i < RECEIVER_COUNT - 1)
            Serial.print(seperator);
    }

    Serial.println();
}

#ifdef TEMP_MONITORING_ENABLED
void writeTempMonitorData() {
    static const char* prefix = "t ";

    Serial.print(prefix);
    Serial.print(tempMonitor.value);
    Serial.println();
}
#endif

#ifdef VOLTAGE_MONITORING_ENABLED
void writeVoltMonitorData() {
    static const char* prefix = "v ";

    Serial.print(prefix);
    Serial.print(voltMonitor.value);
    Serial.println();
}
#endif

void parseCommands() {
    if (Serial.available() > 0) {
        char command = Serial.read();

        switch (command) {
            // Set Frequency
            case 'f':
                uint8_t receiverIndex = Serial.parseInt();
                uint16_t frequency = Serial.parseInt();

                if (receiverIndex == 0 && frequency == 0)
                    break;

                if (receiverIndex < 0 || receiverIndex >= RECEIVER_COUNT)
                    break;

                receivers[receiverIndex].setFrequency(frequency);
                break;
        }

        Serial.find('\n');
        Serial.println("ok");
    }
}
