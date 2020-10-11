#include <Arduino.h>
#include <Wire.h>

#include "RTClib.h" 

// define the pins for hour, minute, second
// only PWM pins can be used: https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
#define PIN_METER_HOUR 5
#define PIN_METER_MIN 6
#define PIN_METER_SEC 3

// PWM values range from 0-255
// tweak these for each meter as needed

#define MINIMUM_PWM_VALUE_HOUR 10
#define MAXIMUM_PWM_VALUE_HOUR 255
#define MINIMUM_PWM_VALUE_MIN 10
#define MAXIMUM_PWM_VALUE_MIN 255
#define MINIMUM_PWM_VALUE_SEC 10
#define MAXIMUM_PWM_VALUE_SEC 255

RTC_DS1307 rtc;

void setup () {
  pinMode(PIN_METER_HOUR, OUTPUT);
  pinMode(PIN_METER_MIN, OUTPUT);
  pinMode(PIN_METER_SEC, OUTPUT);

  rtc.begin();

  // setting the rtc chip time:
  // DateTime(%Y, %m, %d, %I, %M, %S)
  // hours is 12-hour clock
  // none of the values can have leading zeros

  // command to execute prior to upload:
  // date +"rtc.adjust(DateTime(%Y, %m, %d, %I, %M, %S));" | sed -e 's/ 0/ /g'
}

void loop () {
    updateTime();

    // pause one second
    delay(1000);
}

void updateTime() {
  // fetch the current time from the rtc chip
  DateTime now = rtc.now();

  // the hour value is 24-hour format, but the voltmeter needs it in 12-hour
  int8_t hrs = (now.hour() == 0 || now.hour() == 12) ? 12 : now.hour() % 12;
  analogWrite(PIN_METER_HOUR, map(hrs, 1, 12, MINIMUM_PWM_VALUE_HOUR, MAXIMUM_PWM_VALUE_HOUR));

  // minutes and seconds can be mapped more directly
  analogWrite(PIN_METER_MIN, map(now.minute(), 0, 60, MINIMUM_PWM_VALUE_MIN, MAXIMUM_PWM_VALUE_MIN));
  analogWrite(PIN_METER_SEC, map(now.second(), 0, 60, MINIMUM_PWM_VALUE_SEC, MAXIMUM_PWM_VALUE_SEC));
}
