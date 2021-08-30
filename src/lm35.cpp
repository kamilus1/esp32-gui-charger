#include "lm35.hpp"


const uint16_t LM35::max_adc = 1500;
LM35::LM35(){
    this->pin = 2;
}

LM35::LM35(uint8_t adc_pin){
    this->pin = adc_pin;
    
}

uint16_t LM35::read_adc(){
    return analogRead(this->pin);
}

float LM35::convert_temperature(uint16_t adc){
    float temp = (float)adc;
    temp /= max_adc;
    return temp * 150;
}