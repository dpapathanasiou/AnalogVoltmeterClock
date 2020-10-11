# Arduino Analog Voltmeter Clock

## About

This project provides code and wiring diagrams for building a clock using three analog voltmeters in [Arduino](https://www.arduino.cc/), along with a [DS3231 Real Time Clock (RTC)](https://amzn.to/2GSADPZ) chip.

## Parts

* [Arduino Nano](https://amzn.to/33PhFm5) or a [clone](https://amzn.to/36QHK6l)
* 3 [Analog Voltmeters (5 volt)](https://amzn.to/34KMszY): one each for hours, minutes, seconds
* [DS3231 Real Time Clock (RTC)](https://amzn.to/2GSADPZ) chip

## Wiring

### DS3231 to Arduino

* GND -> Arduino GND
* VCC -> Arduino 5V
* SDA -> Arduino Uno A4
* SCL -> Arduino Uno A5

### Each voltmeter to Arduino

* - (negative) -> Arduino GND
* + (positive) -> Arduino [PWM Pin](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/)

*note:* not every digital pin supports [pulse wave modulation (PWM)](http://arduino.cc/en/Tutorial/PWM); check [this guide](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/) to find the correct pins by Arduino model.

## Setting the time

With a battery connected to the RTC chip, replace [line 38 of the sketch](AnalogVoltmeterClock.ino#L38), using this command, just prior to uploading the sketch to the device:

```sh
date +"rtc.adjust(DateTime(%Y, %m, %d, %I, %M, %S));" | sed -e 's/ 0/ /g'
```

## Acknowledgements

* [Michael Teeuw's Analog Voltmeter Clock](https://michaelteeuw.nl/post/174972004187/what-time-is-it-fathers-day)
* [Voltmeter Clock Tutorial](https://create.arduino.cc/projecthub/markbennettuk/voltmeter-clock-fa437b)
* [Adafruit RTC Arduino Library](https://github.com/adafruit/RTClib)
