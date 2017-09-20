# wizardtracker-hardware

This project contains the hardware and firmware for the PropNuts WizardTracker,
an RSSI-based lap timer for drone racing.

## Hardware

The KiCad files can be found under `hardware/`.

The current revision (v2) allows for a total of either eight receivers, or six
receivers with voltage and temperature monitoring. A voltage regulator and XT60
are mounted onboard to provide power.

<a href="https://oshpark.com/shared_projects/VPjVFjat">
  <img src="https://oshpark.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park">
</a>

### Parts List

You can put together a full system for around ~£65.

- [RX5808s (6x or 8x)](https://www.banggood.com/FPV-5_8G-Wireless-Audio-Video-Receiving-Module-RX5808-p-84775.html?p=U103211727939201506N)
- [Arduino Nano](https://www.banggood.com/ATmega328P-Nano-V3-Controller-Board-Compatible-Arduino-p-940937.html?p=U103211727939201506N)
- [BEC (5V)](https://www.banggood.com/Diatone-Mini-2A-BEC-V2_0-Version-3_3V-5V-12V-For-RC-Multirotors-p-1032859.html?p=U103211727939201506N)
- [XT60](https://www.banggood.com/10X-XT60-Male-Female-Bullet-Connectors-Plugs-For-RC-Battery-p-958017.html?p=U103211727939201506N)
- [LM35](https://www.banggood.com/3Pcs-LM35DZ-TO-92-LM35-Precision-Centigrade-Temperature-Sensor-p-1091397.html?p=U103211727939201506N)
- [Resistors (1x 330, 1x 10k, 1x 100k)](https://www.banggood.com/Wholesale-Metal-Film-Resistor-Assorted-Kit-30-Kinds-Value-Total-600pcs-20pcs-Each-p-53320.html?p=U103211727939201506N)
- [LEDs](https://www.banggood.com/100pcs-3mm-LED-Light-emitting-Diode-5-Colors-Electronic-Component-Pack-p-1106574.html?p=U103211727939201506N)
- [Schottky Diode](https://www.banggood.com/10pcs-SB5100-5_0A-SCHOTTKY-BARRIER-Diode-100V-5A-p-1006489.html?p=U103211727939201506N)
- [Pin Headers](https://www.banggood.com/10-Pcs-40-Pin-2_54mm-Single-Row-Male-Pin-Header-Strip-For-Arduino-p-918427.html?p=U103211727939201506N)

_These are affiliate links._

## Firmware

1. Grab the latest version of the Arduino IDE.
2. Clone the repository and open `firmware/firmware.ino`.
3. Compile and flash the code.
4. Pray the magic smoke stays in.

### Protocol

On boot, the firmware opens serial at `115200bps`. After a short delay it will
begin sending RSSI values for each module seperated by a tab, ending in a new
line. e.g.:

    110    \t    220    \t    150    \t    243    \n
    140    \t    231    \t    143    \t    192    \n
    ...etc

## Acknowledgements

The source code for this project is based on [my rx5808-pro-diversity rewrite](https://github.com/Knifa/rx5808-pro-diversity/tree/tidy-up).

## License

This project is licensed under the terms of the MIT license.
