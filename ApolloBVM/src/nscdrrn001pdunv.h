#ifndef nscdrrn001pdunv_h
#define nscdrrn001pdunv_h
#include "wiring_private.h"



//#include "SoftwareSerial.h"

using byte = unsigned char;

class Nscdrrn001pdunv {

  public:
    Nscdrrn001pdunv(uint8_t pin, float pressure_conversion_multiplier, float pressure_conversion_constant );

    float read();
    float convertToPressure(int input);


  private:
    //SoftwareSerial* _serial_ptr;
    // output (cmH20) = _pressure_conversion_multiplier * input + _pressure_conversion_constant
    float _pressure_conversion_multiplier = 0.169618; 
    float _pressure_conversion_constant = -71.3247129;
    float _pressure_max = 40; // 40cmH2O
    uint8_t _pin;



};


#endif
