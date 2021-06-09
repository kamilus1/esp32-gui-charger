#include <ADBMS1818.hpp>


class ADBMS1818Class : public ADBMS1818{

public:
    ADBMS1818Class(uint8_t port,  uint8_t csPin, uint8_t n = 1, uint32_t freq= 1000000, uint8_t br = 6): ADBMS1818(port, csPin, n, freq, br){

    }
    ADBMS1818Class(int8_t spi_pins[4], uint8_t n = 1, uint32_t freq= 1000000, uint8_t br = 6): ADBMS1818(spi_pins, n, freq, br){

    }
    ADBMS1818Class(uint8_t cspin, uint8_t n, uint32_t freq,  uint8_t br): ADBMS1818(cspin, n, freq, br){
        
    }
};