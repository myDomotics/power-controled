# power-controled
5V power rail controled by Arduino and ESP8266
Design to replace individual power plugs on different devices

## Features
- 5V/5A output
- 5 separated outputs. 4 of them could be switch on/off locally or remotely through mqtt
- display amp and internal temperature
- fan controled based on temperature

Technical design details :
- display is TM1637 based
- temperature sensor : DB1820
- amp sensor is ACS711EX based
- fan size 90x90 cm/12V
- power : Meanwell 5V/5A - 12V 1A (reuse from old project)
- use relays to switch on/off 5V outputs


