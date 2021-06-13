#include "ina238.hpp"
std::map<std::string, uint8_t> ina238::registers = {
    {"CONFIG_1", 0x00},
    {"ADCCONFIG_2", 0x01},
    {"CURRLSBCALC_3", 0x02},
    {"VSHUNT", 0x04},
    {"VBUS", 0x05},
    {"DIETEMP", 0x06},
    {"CURRENT", 0x07},
    {"POWER", 0x08},
    {"DIAG_ALERT", 0x0b},
    {"SOVL", 0x0c},
    {"SUVL", 0x0d},
    {"BOVL", 0x0e},
    {"BUVL", 0x0f},
    {"TEMP_LIMIT", 0x10},
    {"PWR_LIMIT", 0x11},
    {"MAFUCATURER_ID", 0x3e},
    {"DEVICE_ID", 0x3f}
};
ina238::ina238(uint16_t addr, uint8_t sda, uint8_t scl, uint32_t freq,  uint8_t i2c_bus): ina_addr(addr){
    i2c_wire = new TwoWire(i2c_bus);
    i2c_wire->begin(sda, scl, freq);
}

ina238::ina238(uint16_t addr, TwoWire *two_wire): ina_addr(addr){
    i2c_wire = two_wire;
}

bool ina238::device_found(){
    i2c_wire->beginTransmission(ina_addr);
    uint8_t error;
    error = i2c_wire->endTransmission();
    return error == 0;
}


void ina238::write_command(uint8_t *data){
    uint8_t arr_size = sizeof(data)/sizeof(data[0]);
    i2c_wire->beginTransmission(this->ina_addr);
    for(uint8_t i=0;i<arr_size;i++){
        i2c_wire->write(data[i]);
    }
    i2c_wire->endTransmission();
}

uint8_t *ina238::read_command(uint8_t *data, uint8_t qnt){
    uint8_t *read_data = new uint8_t[qnt];
    this->write_command(data);
    i2c_wire->requestFrom(this->ina_addr, qnt);
    for(uint8_t i=0;i<qnt;i++){
        while(!i2c_wire->available());
        read_data[i] = i2c_wire->read();
    }
    return read_data;
}