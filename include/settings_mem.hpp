#include <EEPROM.h>
#include <map>


typedef union{
    float value;
    uint8_t value_bytes[4];
} mem_float;
typedef union{
    int value;
    uint8_t value_bytes[4];
} mem_int;

class MemManager{
    static const std::map<std::string, std::pair<uint8_t, uint8_t>>memory_map; 
    static const uint16_t mem_size;
    uint8_t adbms_quantity;
    protected:
        uint8_t *read(uint8_t addr, uint16_t len);
        void write(uint8_t addr, uint8_t *data, uint16_t len);
    public:
        MemManager();
        void reset();
        void updateValues();
        bool firstUse();
        void clear(); 
        uint8_t getADBMSQuantity();
        void setADBMSQuantity(uint8_t data);

};