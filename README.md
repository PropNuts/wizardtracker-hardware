# wizardtracker-hardware

This project contains the hardware and firmware for the PropNuts WizardTracker,
an RSSI-based lap timer for drone racing.

## Hardware

The KiCad files can be found under `hardware/`.

<p align="center">
  <img width="600" src="https://github.com/PropNuts/wizardtracker-hardware/blob/master/media/pcb.png">
</p>

The current revision (v2) allows for a total of either eight receivers, or six
receivers with voltage and temperature monitoring. A voltage regulator and XT60
are mounted onboard to provide power.

<p>
  <a href="https://oshpark.com/shared_projects/VPjVFjat">
    <img src="https://oshpark.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park">
  </a>
</p>

### Parts List

You can put together a full system for around ~£65.

- [RX5808s (6x or 8x)](https://www.banggood.com/FPV-5_8G-Wireless-Audio-Video-Receiving-Module-RX5808-p-84775.html?p=U103211727939201506N)
- [Arduino Nano](https://www.banggood.com/ATmega328P-Nano-V3-Controller-Board-Compatible-Arduino-p-940937.html?p=U103211727939201506N)
- [BEC (5V)](https://www.banggood.com/Diatone-Mini-2A-BEC-V2_0-Version-3_3V-5V-12V-For-RC-Multirotors-p-1032859.html?p=U103211727939201506N)
- [XT60](https://www.banggood.com/10X-XT60-Male-Female-Bullet-Connectors-Plugs-For-RC-Battery-p-958017.html?p=U103211727939201506N)
- [LM35](https://www.banggood.com/3Pcs-LM35DZ-TO-92-LM35-Precision-Centigrade-Temperature-Sensor-p-1091397.html?p=U103211727939201506N)
- [Resistors (1x 330, 1x 10k, 1x 100k)](https://www.banggood.com/Wholesale-Metal-Film-Resistor-Assorted-Kit-30-Kinds-Value-Total-600pcs-20pcs-Each-p-53320.html?p=U103211727939201506N)
- [LEDs](https://www.banggood.com/100pcs-3mm-LED-Light-emitting-Diode-5-Colors-Electronic-Component-Pack-p-1106574.html?p=U103211727939201506N)
- [Schottky Diode (1x 1N5817)](https://www.banggood.com/100-Pcs-030892-Diodes-Package-Rectifier-Schottky-8-Type-In-Component-Box-p-1164787.html?p=U103211727939201506N)
- [Pin Headers](https://www.banggood.com/10-Pcs-40-Pin-2_54mm-Single-Row-Male-Pin-Header-Strip-For-Arduino-p-918427.html?p=U103211727939201506N)

_These are affiliate links._

## Firmware

1. Grab the latest version of the Arduino IDE.
2. Clone the repository and open `firmware/firmware.ino`.
3. Edit `Config.h` to your needs.
4. Compile and flash the code.
5. Pray the magic smoke stays in.

### Protocol

On boot, the firmware opens serial at `250000bps`. After a short delay, it will
begin sending RSSI values for each module, seperated by a space, ending in a new
line. Each line is prefixd with `r `.

In calibrated output mode, values range between `0` to `255`. In raw output
mode (default), values range between `0` to  `1023`.

    < r 110 220 150 243 135 254
    < r 140 231 143 192 148 244
    ... etc

If enabled, voltage and temperature values will be sent periodically. Voltage
is prefixed with `v ` and temperature is prefixed with `t `.

    < v 16.08
    < t 56.33
    ... etc

#### Commands

The command parser is extremely niave, with little to no error checking. Expect
strange results with malformed commands. All command should end in a new line
character.

Frequencies can be set by sending `f <index> <frequency>`. These frequencies
will be saved and reloaded on startup.

    > f 0 5745
    < ok
    > f 1 5975
    < ok
    ... etc

Modules can be calibrated using `n` (minimum) and `m` (maximum). These
calibration values will be saved and reloaded on startup. The device must be
rebooted for calibration to take effect.

    [all modules set to same frequency]
    [transmitter powered down]
    > n
    < ok
    [transmitter powered up]
    > m
    < ok

Output can be toggled between raw output using `r`, and calibration output
using `s`. The default mode is raw output. This setting is saved and will be
reloaded on startup.

    > r
    < ok
    < r 395 345 299 405 514 445
    < ... etc
    > s
    < ok
    < r 0 5 8 1 10 13
    < ... etc

Information about the device can be requested using `?`. The device will respond
in the format `? <module count> <frequency 1>...<frequency n> <raw mode>`.

    > ?
    < ? 6 5695 5695 5695 5695 5695 5695 1
    [6 receivers all on 5695MHz, with raw mode enabled]
    < ok

## Acknowledgements

The source code for this project is based on [my rx5808-pro-diversity rewrite](https://github.com/Knifa/rx5808-pro-diversity/tree/tidy-up).

## License

This project is licensed under the terms of the MIT license.
