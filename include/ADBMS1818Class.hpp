#include <ADBMS1818.hpp>
#define COMM_STOPPED 0
#define COMM_ACTIVE 1

class ADBMS1818Class : public ADBMS1818{
    uint8_t * cell_qnt;
    uint32_t tot_cell_qnt;
    uint8_t adbms_status;
    static const float vcell_min_exist;
    static const float vcell_max;
public:
    ADBMS1818Class(uint8_t port,  uint8_t csPin, uint8_t n = 1, uint32_t freq= 1000000, uint8_t br = 6): ADBMS1818(port, csPin, n, freq, br){
        cell_qnt = new uint8_t(n);
        adbms_status = COMM_ACTIVE;
    }
    ADBMS1818Class(int8_t spi_pins[4], uint8_t n = 1, uint32_t freq= 1000000, uint8_t br = 6): ADBMS1818(spi_pins, n, freq, br){
        cell_qnt = new uint8_t(n);
        adbms_status = COMM_ACTIVE;
    }
    ADBMS1818Class(uint8_t cspin, uint8_t n, uint32_t freq,  uint8_t br): ADBMS1818(cspin, n, freq, br){
        cell_qnt = new uint8_t(n);
        adbms_status = COMM_ACTIVE;
    }
    void start_all_conversions();
    void start_cell_ballancing(uint8_t value = 1);
    bool cell_detect();
    uint32_t get_tot_cell_qnt();
    float get_sum_cell_voltage();
    uint8_t * get_cell_qnt();
    uint8_t get_status();
    int voltage_percent(float voltage_value);
};