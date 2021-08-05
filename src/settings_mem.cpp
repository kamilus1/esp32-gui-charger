#include "settings_mem.hpp"


const std::map<std::string, std::pair<uint8_t, uint8_t>> MemManager::memory_map = {
    {"FIRST", {0, 1}},
    {"ADBMS_QNT", {1, 1}},

};

const uint16_t MemManager::mem_size = 32;


MemManager::MemManager(){
    EEPROM.begin(this->mem_size);
}

bool MemManager::firstUse(){
    return EEPROM.read(std::get<0>(this->memory_map.at("FIRST")));
}

uint8_t * MemManager::read(uint8_t addr, uint16_t len){
    uint8_t *buffer = new uint8_t [len];
    for(uint16_t i=0; i<len;i++){
        buffer[i] = EEPROM.read((addr + i));
    }
    return buffer;
}

void MemManager::write(uint8_t addr, uint8_t *data, uint16_t len){
    for(uint16_t i=0;i<len;i++){
        EEPROM.write((addr + i), data[i]);
    }
}

void MemManager::clear(){
    uint8_t clear_data[this->mem_size] = {0};
    this->write(0, clear_data, this->mem_size);
}

uint8_t MemManager::getADBMSQuantity(){
    return this->adbms_quantity;
}

void MemManager::setADBMSQuantity(uint8_t data){
    this->adbms_quantity = data;
    this->write(std::get<0>(this->memory_map.at("ADBMS_QNT")), &this->adbms_quantity, std::get<1>(this->memory_map.at("ADBMS_QNT")));
}