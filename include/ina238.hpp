#include <Wire.h>
#include <map>

class ina238{
    TwoWire *i2c_wire;
    uint16_t ina_addr;
    static std::map<std::string, uint8_t> registers;
    public:
        ina238(uint16_t addr, uint8_t sda=21, uint8_t scl=22, uint32_t freq=400000,  uint8_t i2c_bus = 0);
        ina238(uint16_t addr, TwoWire *two_wire);
        bool device_found();
        void write_command(uint8_t *data);
        uint8_t *read_command(uint8_t *data, uint8_t qnt);

};