#include "buzzer.h"
#include "Arduino.h"
#include "pins_arduino.h"
    Buzzer::Buzzer(byte pin):
        _pin(pin)
    {}
    void Buzzer::alarmHigh(){
        tone(_pin, 5000);
        delay(100);
        noTone(_pin); 
    }
    void Buzzer::alarmLowPressure(){
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
    void Buzzer::alarmHighPressure(){
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