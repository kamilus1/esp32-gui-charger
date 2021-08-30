#include <Arduino.h>

class LM35{
    private:
        uint8_t pin;
        static const uint16_t max_adc;
    public:
        LM35();
        LM35(uint8_t adc_pin);
        uint16_t read_adc();
        static float convert_temperature(uint16_t adc);
}; 