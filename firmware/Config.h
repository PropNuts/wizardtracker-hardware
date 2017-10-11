#ifndef CONFIG_H
#define CONFIG_H


// Receivers
// ==============

// Number of receivers on the board. Make sure these are sequentially connected
// to the pins --- no gaps!
#define RECEIVER_COUNT 6

#define RECEIVER_PIN_SPI_CLK 2
#define RECEIVER_PIN_SPI_DATA 3
#define RECEIVER_PIN_SPI_SS_START 11
#define RECEIVER_PIN_RSSI_START A0


// Temperature Monitoring
// ======================
#define TEMP_MONITORING_ENABLED

#ifdef TEMP_MONITORING_ENABLED
    #define TEMP_MONITORING_PIN A7

    // Multiplier for raw ADC value to get to celcius. Defaults work for the
    // LM35  at 0.01V/C.
    #define TEMP_MONITORING_MULTIPLIER (((1.0f / 1024.0f) * 5.0f) / 0.01f)
#endif


// Voltage Monitoring
// ==================
#define VOLTAGE_MONITORING_ENABLED

#ifdef VOLTAGE_MONITORING_ENABLED
    #define VOLTAGE_MONITORING_PIN A6

    // Multiplier for raw ADC value to get to volts. Defaults work for a 1:11
    // divider.
    #define VOLTAGE_MONITORING_MULTIPLIER (1.0f / 1024.0f * 5.0f * 11.0f)
#endif


// Serial
// ====

#define SERIAL_BAUD 250000

// Delay between RSSI messages. Too fast and the buffer clogs and things get
// weird. 3ms is a good default value.
#define RSSI_DELAY_MS 3

// Delay between monitoring messages.
#define MONITORING_DELAY_MS 10000


// Misc
// ====

// Delay to wait for modules to settle, etc.
#define BOOT_DELAY_MS 1000


// =============================================================================


#define LED_PIN 13

#if defined(VOLTAGE_MONITORING_ENABLED) || defined(TEMP_MONITORING_ENABLED)
    #define MONITORING_ENABLED
#endif


#endif
