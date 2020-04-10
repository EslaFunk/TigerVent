#ifndef lcd2004_h
#define lcd2004_h

#include "Arduino.h"
#include <LiquidCrystal.h>



//#include "SoftwareSerial.h"

using byte = unsigned char;

class Lcd2004 {

  public:
    Lcd2004(byte pin);

    void begin(int baud);

    void print(String st);
    void print(int val);
    void println(String st);
    //void print(int num);
    
    void setBacklight(byte brightness);
    void clearDisplay();
    void setCursor(byte cursor_position, byte line);

    void underlineOn();
    void underlineOff();

    void blinkingOn();
    void blinkingOff();

    void moveCursorRight();
    void moveCursorLeft();

    void backspace();
    void remove();

    String zeroPad(int in);

  private:
    //SoftwareSerial* _serial_ptr;

    byte _row;
    byte _col;

    LiquidCrystal* _lcd;



};


#endif
