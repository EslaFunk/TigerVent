#ifndef nscdrrn001pdunv_h
#define nscdrrn001pdunv_h




//#include "SoftwareSerial.h"

using byte = unsigned char;

class Nscdrrn001pdunv {

  public:
    Nscdrrn001pdunv(byte pin, float pressure_multiplier, );

    int read();


  private:
    //SoftwareSerial* _serial_ptr;
    float pressure_multiplier;
    float 



};


#endif
