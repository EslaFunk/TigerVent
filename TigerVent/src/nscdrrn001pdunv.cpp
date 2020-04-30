#include "nscdrrn001pdunv.h"

Nscdrrn001pdunv::Nscdrrn001pdunv(uint8_t pin, float pressure_conversion_multiplier, float pressure_conversion_constant  ):
    _pin(pin),
    _pressure_conversion_multiplier(pressure_conversion_multiplier),
    _pressure_conversion_constant(pressure_conversion_constant)
{}

int Nscdrrn001pdunv::read(){
    return convertToPressure(analogRead(_pin));
}

int Nscdrrn001pdunv::convertToPressure(int input){
    return (int) ( (_pressure_conversion_multiplier * input) + _pressure_conversion_constant );
}
