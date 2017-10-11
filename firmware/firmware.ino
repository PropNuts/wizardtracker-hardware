#include <stdint.h>
#include <avr/pgmspace.h>

#include "Config.h"

#include "EepromSettings.h"
#include "Receiver.h"
#include "Monitor.h"
#include "Timer.h"


#ifndef cbi
    #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
    #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


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


const char serialSeperator = ' ';


void setup() {
    enableFastAdcRead();

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

    EepromSettings.load();

    // Wait for modules to settle.
    delay(BOOT_DELAY_MS);

    // Configure receivers.
    for (uint8_t i = 0; i < RECEIVER_COUNT; i++) {
        receivers[i].init(
            RECEIVER_PIN_SPI_CLK,
            RECEIVER_PIN_SPI_DATA,
            RECEIVER_PIN_SPI_SS_START - i,
            RECEIVER_PIN_RSSI_START + i,
            EepromSettings.rssiMin[i],
            EepromSettings.rssiMax[i]
        );

        receivers[i].setFrequency(EepromSettings.frequency[i]);
    }

    rssiTimer.reset();
    #ifdef MONITORING_ENABLED
        monitorTimer.reset();
    #endif

    Serial.begin(SERIAL_BAUD);

    // Ready to go!
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
    Serial.print(F("r "));

    for (uint8_t i = 0; i < RECEIVER_COUNT; i++) {
        if (EepromSettings.rawMode)
            Serial.print(receivers[i].rssiRaw, DEC);
        else
            Serial.print(receivers[i].rssi, DEC);

        if (i < RECEIVER_COUNT - 1)
            Serial.print(serialSeperator);
    }

    Serial.println();
}

#ifdef TEMP_MONITORING_ENABLED
void writeTempMonitorData() {
    Serial.print(F("t "));
    Serial.print(tempMonitor.value, 2);
    Serial.println();
}
#endif

#ifdef VOLTAGE_MONITORING_ENABLED
void writeVoltMonitorData() {
    Serial.print(F("v "));
    Serial.print(voltMonitor.value, 2);
    Serial.println();
}
#endif

void parseCommands() {
    if (Serial.available() > 0) {
        const char command = Serial.read();

        switch (command) {
            // Status
            case '?': {
                Serial.print(F("? "));
                Serial.print(RECEIVER_COUNT, DEC);
                Serial.print(serialSeperator);

                for (uint8_t i = 0; i < RECEIVER_COUNT; i++) {
                    Serial.print(EepromSettings.frequency[i]);
                    Serial.print(serialSeperator);
                }

                Serial.print(EepromSettings.rawMode ? 1 : 0, DEC);
                Serial.println();
            } break;

            // Set frequency.
            case 'f': {
                uint8_t receiverIndex = Serial.parseInt();
                uint16_t frequency = Serial.parseInt();

                if (receiverIndex == 0 && frequency == 0)
                    break;

                if (receiverIndex < 0 || receiverIndex >= RECEIVER_COUNT)
                    break;

                receivers[receiverIndex].setFrequency(frequency);
                EepromSettings.frequency[receiverIndex] = frequency;
                EepromSettings.save();
            } break;

            // Calibrate minimum RSSI values.
            case 'n': {
                for (uint8_t i = 0; i < RECEIVER_COUNT; i++) {
                    EepromSettings.rssiMin[i] =
                        (uint16_t) receivers[i].rssiRaw * 0.975f;
                }

                EepromSettings.save();
            } break;

            // Calibrate maximum RSSI values.
            case 'm': {
                for (uint8_t i = 0; i < RECEIVER_COUNT; i++) {
                    EepromSettings.rssiMax[i] =
                        (uint16_t) receivers[i].rssiRaw * 1.025f;
                }

                EepromSettings.save();
            } break;

            // Enable raw mode.
            case 'r': {
                EepromSettings.rawMode = true;
                EepromSettings.save();
            } break;

            // Disable raw mode.
            case 's': {
                EepromSettings.rawMode = false;
                EepromSettings.save();
            } break;
        }

        Serial.find('\n');
        Serial.println(F("ok"));
    }
}

void enableFastAdcRead() {
    sbi(ADCSRA, ADPS2);
    cbi(ADCSRA, ADPS1);
    cbi(ADCSRA, ADPS0);
}
