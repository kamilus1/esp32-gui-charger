#include "ADBMS1818Class.hpp"

const float ADBMS1818Class::vcell_min_exist = 1000.0;

void ADBMS1818Class::start_all_conversions(){
    this->start_cv_adc_conversion();
    while(!this->pladc_rdy());
    this->start_open_wire_conversion();
    while(!this->pladc_rdy());
    this->start_self_test_conversion();
    while(!this->pladc_rdy());
    this->start_overlap_conversion();
    while(!this->pladc_rdy());
    this->start_gpio_adc_conversion();
    while(!this->pladc_rdy());
    this->start_gpio_adc_conversion_dr();
    while(!this->pladc_rdy());
    this->start_gpio_open_wire_conversion();
    while(!this->pladc_rdy());
    this->start_self_test_gpio_conversion();
    while(!this->pladc_rdy());
    this->start_status_adc_conversion();
    while(!this->pladc_rdy());
    this->start_status_adc_dr_conversion();
    while(!this->pladc_rdy());
    this->start_self_test_conversion();
    while(!this->pladc_rdy());
    this->start_cv_gpio12_conversion();
    while(!this->pladc_rdy());
    this->start_cv_sc_conversion();
    while(!this->pladc_rdy());
}

bool ADBMS1818Class::cell_detect(){
    uint16_t **cell_voltage;
    cell_voltage = new uint16_t* [this->n];
    this->adbms_status = COMM_ACTIVE;
    for(uint8_t i=0; i<this->n;i++){
        cell_voltage[i] = new uint16_t [18];
        for(uint8_t j=0;j<18;j++){
            cell_voltage[i][j] = 0;
        }
        this->cell_qnt[i]  = 0;
    }
    this->tot_cell_qnt = 0;
    this->start_cv_sc_conversion();
    cell_voltage = this->read_cv_adc();
    for(uint8_t i=0; i<this->n; i++){
        uint8_t j = 0;
        while(j<18&&(this->convert_voltage(cell_voltage[i][j])*1000.0)>=this->vcell_min_exist){
            j++;
        }
        this->cell_qnt[i] = j;
        this->tot_cell_qnt += j;
        while(j<18){
            if(this->convert_voltage(cell_voltage[i][j])*1000.0 >= this->vcell_min_exist){
                this->adbms_status = COMM_STOPPED;
                return false;
            }
            j++;
        }
    }
    return true;
}

uint32_t ADBMS1818Class::get_tot_cell_qnt(){
    return this->tot_cell_qnt;
}

uint8_t* ADBMS1818Class::get_cell_qnt(){
    return this->cell_qnt;
}

uint8_t ADBMS1818Class::get_status(){
    return this->adbms_status;
}

float ADBMS1818Class::get_sum_cell_voltage(){
    this->start_cv_sc_conversion();
    if(this->pladc_rdy()){
        uint16_t **cell_voltage;
        cell_voltage = new uint16_t* [this->n];
        for(uint8_t i=0; i<this->n;i++){
            cell_voltage[i] = new uint16_t [18];
            for(uint8_t j=0;j<18;j++){
                cell_voltage[i][j] = 0;
            }
        }
        cell_voltage = this->read_cv_adc();
        float voltage_sum = 0;
        for(uint8_t i=0; i<this->n; i++){
            for(uint8_t j=0; j<this->cell_qnt[i]; j++){
                voltage_sum += this->convert_voltage(cell_voltage[i][j]);
            }
        }
        return voltage_sum;
    }else{
        return 0;
    }
}