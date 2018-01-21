# power-controled
5V power rail controled by Arduino and ESP8266
Design to replace individual power plugs on different devices

## Features
- 5V/5A output
- 5 separated outputs. 4 of them could be switch on/off locally or remotely through mqtt
- display amp and internal temperature
- fan controled based on temperature

## BOM:
### Arduino card:
#### ICs's
- ATMega328 with Arduino bootloader
- 7805
#### Resistors
- 10k
#### Capacitors
- 100uF
- 10uF
- 3*100nF
- 2*22pF
#### Miscelaneous
- screw terminal 2 position
- pin headers (9)
