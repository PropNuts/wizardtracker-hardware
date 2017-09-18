# wizardtracker-hardware

This project contains the firmware for the PropNuts WizardTracker, an RSSI-based lap timer for drone racing.

## Hardware

The KiCad files can be found under `hardware/`.

<a href="https://oshpark.com/shared_projects/VPjVFjat">
  <img src="https://oshpark.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park">
</a>

## Firmware

1. Grab the latest version of the Arduino IDE.
2. Clone the repository and open `WizardTracker.ino`.
3. Compile and flash the code.
4. Pray the magic smoke stays in.

## Protocol

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
