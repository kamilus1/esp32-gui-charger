#include <Arduino.h>
#include <SPI.h>
#include <map>
#include <stdlib.h>
#include <vector>

#define DEFAULT_ADC_7kHz 2

#define DISC_PERM 1
#define DISC_NPERM 0

//use default configuration for now.
class ADBMS1818{
    private:
        SPIClass spi;
        static std::map<std::string, uint16_t> commands;
        static std::map<std::string, uint8_t> commands_bits;
        static void u16_to_u8(uint16_t x, uint8_t *y);
        uint32_t f;
        uint8_t cs, n, byte_reg;
        uint8_t *read_buff;
        uint8_t *write_buff;
        uint16_t pec15Table[256];
        uint16_t pec;
        void init_pec_15_table();
        void pec_15(uint8_t *tab, uint8_t len);
        void poll_command(uint8_t command[2]);
        void write_command(uint8_t command[2], uint8_t*data);
        bool read_command(uint8_t command[2], uint8_t *data);
        void init();
        uint16_t config_md_bits(uint16_t command);
        uint16_t config_ch_bits(uint16_t command, std::string key="CH");
        uint16_t config_st_bits(uint16_t command);
        uint16_t config_pup_bit(uint16_t command);
        uint16_t config_dcp_bit(uint16_t command);
        uint16_t config_bit(uint16_t command, uint8_t pos, bool bit);
    public:
        
        ADBMS1818(uint16_t port,  uint8_t csPin, uint32_t freq= 500000, uint8_t n = 1, uint8_t br = 6);
        ADBMS1818(int8_t spi_pins[4], uint32_t freq= 500000, uint8_t n = 1, uint8_t br = 6);
        ADBMS1818(uint8_t csPin, uint32_t freq= 500000, uint8_t n = 1, uint8_t br = 6);
        void begin();
        void wake_up(uint8_t dur=200);
        void set_config_reg_a();
        void set_config_reg_b();
        void set_bits(std::string bit_key, uint8_t bit_value);
        void start_cv_adc_conversion(); //for default mode with 7khz  freq it takes about 2.3 ms for all cells conversion. 
        uint16_t* read_cv_adc(uint16_t cells_voltage[18]);
    
};