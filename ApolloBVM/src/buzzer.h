#ifndef buzzer_h
#define buzzer_h

using byte = unsigned char;

class Buzzer {

  public:
    Buzzer(byte pin);
    
    void alarmHigh();
    void alarmLowPressure();
    void alarmHighPressure();


  private:
    byte _pin;



};


#endif