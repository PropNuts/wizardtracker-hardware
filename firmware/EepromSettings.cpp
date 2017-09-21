#include <Arduino.h>
#include <EEPROM.h>

#include "EepromSettings.h"


struct EepromSettings EepromSettings;


void EepromSettings::load() {
    EEPROM.get(0, *this);

    if (this->magic != EEPROM_MAGIC)
        this->initDefaults();
}

void EepromSettings::save() {
    EEPROM.put(0, *this);
}


void EepromSettings::initDefaults() {
    memcpy_P(this, &EepromDefaults, sizeof(EepromDefaults));
    this->save();
}
