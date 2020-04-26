#include "buzzer.h"
#include "Arduino.h"
#include "pins_arduino.h"
Buzzer::Buzzer(byte pin) : _pin(pin)
{
    _alarmStatus = NoAlarm;
}
void Buzzer::alarmHigh()
{
    tone(_pin, 5000);
    delay(100);
    noTone(_pin);
}
void Buzzer::alarmIncreasing()
{
    tone(_pin, 5000);
    delay(25);
    tone(_pin, 3500);
    delay(25);
    tone(_pin, 2000);
    delay(25);
    tone(_pin, 500);
    delay(25);
    noTone(_pin);
}
void Buzzer::alarmDecreasing()
{
    tone(_pin, 500);
    delay(25);
    tone(_pin, 2000);
    delay(25);
    tone(_pin, 3500);
    delay(25);
    tone(_pin, 5000);
    delay(25);
    noTone(_pin);
}

