#include <Wire.h>
#include <map>

class ina238{
    TwoWire *i2c_wire;
    uint16_t ina_addr;
    uint16_t curr_lsb_calc;
    uint8_t write_data [4];
    uint16_t r;

    static std::map<std::string, uint8_t> registers;
    public:
        ina238(uint16_t addr, uint16_t r_shunt = 100, uint8_t sda=21, uint8_t scl=22, uint32_t freq=400000,  uint8_t i2c_bus = 0);
        ina238(uint16_t addr, TwoWire *two_wire, uint16_t r_shunt = 100);
        void begin();
        bool device_found();
        void write_command(uint8_t *data, uint8_t qnt);
        uint8_t *read_command(uint8_t *data, uint8_t wqnt, uint8_t rqnt);
        void write_config1(uint8_t rst = 0, uint8_t convdly = 1, uint8_t adcrange = 1);
        void write_adc_config2(uint8_t mode = 0xb, uint8_t vcvbust = 0x2, uint8_t vshct = 0x2, uint8_t vtct = 0x2, uint8_t avg = 0x0);
        void write_currlsbcalc_3(uint16_t currlsb = 0x0fff);
        float read_current();
        float read_temperature();
        float read_voltage();
};