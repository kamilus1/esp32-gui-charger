#include <Arduino.h>
#include <stdio.h>
#include "GUIslice.h"
#include "ADBMS1818Class.hpp"
#include "ina238.hpp"
#define BAUD_RATE 115200
#define N 1
#define CS 5

//pwm variables
const int freq = 10000; //10 khz
const int pwm_channel = 0;
const int resolution = 12; //12 bit resolution

//pwm pins

const int8_t pwm_pins[3] = {25, 26, 27};

//adbms pins and object
int8_t adbms_pins[4] = {18,19,23,CS};//tab for custom SPI Pins. sck, miso, mosi, cs is a pin order. In this tab i use HSPI port SPI pins
ADBMS1818Class adbms(adbms_pins); //constructor with modified pins
//ADBMS1818 adbms((uint8_t)FSPI, (uint8_t)CS); //construcot with modified CS pin and spi port
//ADBMS1818 adbms(15); //constructor with default SPI and CS pin modifed
//ina238 driver
//address depends on signals attached to A0 and A1 pins of ina238. 
//https://www.ti.com/lit/ds/symlink/ina238-q1.pdf?ts=1623446444912#page=15
ina238 ina((uint16_t)0x40);
//serial demo variables
bool write_state;
uint8_t display_state;
uint8_t balance_state;
uint8_t sctl_pwm_state;
uint8_t pin_sctl_pwm, n_sctl_pwm, value_sctl_pwm;
void setup() {
  //setup PWM
  write_state = true;
  display_state = 0;
  balance_state = 0;
  sctl_pwm_state = 0;
  ledcSetup(pwm_channel, freq, resolution);
  for(uint8_t i=0; i<3;i++){
    ledcAttachPin(pwm_pins[i], pwm_channel);
  }

  pinMode(CS, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  adbms.begin();
}


void start_window();
void adbms_conversions_window();
void adbms_config_window();
void adbms_reads_window();
void adbms_balance_window();
void adbms_balance_options();
void adbms_sctl();
void adbms_pwm();
void ina_config_window();
void ina_reads_window();

void loop() {
  switch(display_state){
    case 0:
      start_window();
      break;
    case 1:
      adbms_conversions_window();
      break;
    case 2:
      adbms_reads_window();
      break;
    case 3:
      adbms_config_window();
      break;
    case 4:
      adbms_balance_window();
      break;
    case 5:
      ina_config_window();
      break;
    case 6:
      ina_reads_window();
      break;
    default: break;
  }  
}


void adbms_conversions_window(){
   if(write_state){
    write_state = false;
    Serial.println();
    Serial.println("0: Cell voltage           1: Open wire");
    Serial.println("2: Self test              3: Overlap");
    Serial.println("4: GPIO                   5: GPIO and DR");
    Serial.println("6: GPIO open wire         7: Self test and GPIO");
    Serial.println("8: Status                 a: Status and DR");
    Serial.println("b: Cell voltage+GPIO1_2   c: Cell voltage and SC");
    Serial.println("d: Conversion done        q: Quit");
  }
  if(Serial.available() > 0){
    char c = Serial.read();
    switch(c){
      case '0':
        Serial.println("Cell voltage conversion begin");
        adbms.start_cv_adc_conversion();
        break;
      case '1':
        Serial.println("Open wire conversion begin");
        adbms.start_open_wire_conversion();
        break;
      case '2':
        Serial.println("Self test conversion begin");
        adbms.start_self_test_conversion();
        break;
      case '3':
        Serial.println("Overlap conversion begin");
        adbms.start_overlap_conversion();
        break;
      case '4':
        Serial.println("GPIO conversion begin");
        adbms.start_gpio_adc_conversion();
        break;
      case '5':
        Serial.println("GPIO and digital redundancy conversion begin");
        adbms.start_gpio_adc_conversion_dr();
        break;
      case '6':
        Serial.println("GPIO open wire conversion begin");
        adbms.start_gpio_open_wire_conversion();
        break;
      case '7':
        Serial.println("Self test and gpio conversion begin");
        adbms.start_self_test_gpio_conversion();
        break;
      case '8':
        Serial.println("Status conversion begin");
        adbms.start_status_adc_conversion();
        break;
      case '9':
        Serial.println("Status and digital redundancy conversion begin");
        adbms.start_status_adc_dr_conversion();
        break;    
      case 'a':
        Serial.println("Self test status conversion begin");
        adbms.start_self_test_status_conversion();
        break;
      case 'b':
        Serial.println("Cell voltage and GPIO 1 2 conversion begin");
        adbms.start_cv_gpio12_conversion();
        break;
      case 'c':
        Serial.println("Cell voltage and SC conversion begin");
        adbms.start_cv_sc_conversion();
        break;  
      case 'd':
        if(adbms.pladc_rdy()){
          Serial.println("Conversion done!");
        }else{
          Serial.println("Conversion not done!");
        }
        break;
      case 'q':
        write_state = true;
        display_state = 0;
      break;
      default :
        break;
    }
}
}

void start_window(){
  if(write_state){
    write_state = false;
    Serial.println();
    Serial.println("0: ADBMS1818 conversions  1: ADBMS1818 reads");
    Serial.println("2: ADBMS1818 config       3: ADBMS1818 cell ballancing");
    Serial.println("4: INA238 config          5: INA238 reads");
  }
  if(Serial.available()>0){
    char c = Serial.read();
    switch(c){
      case '0':
        write_state = true;
        display_state = 1;
        break;
      case '1':
        write_state = true;
        display_state = 2;
        break;
      case '2':
        write_state = true;
        display_state = 3;
      break;
      case '3':
        write_state = true;
        display_state = 4;
      break;
      case '4':
        write_state = true;
        display_state = 5;
      break;
      case '5':
        write_state = true;
        display_state = 6;
      break;
      default:
        break;
    }
  }
}

void adbms_reads_window(){
  if(write_state){
    write_state = false;
    Serial.println();
    Serial.println("0: Cell voltage           1: Auxiliary");
    Serial.println("q: Quit");
  }
  uint16_t **data;
  if(Serial.available()>0){
    char c = Serial.read();
    switch(c){
      case '0':{
        data = adbms.read_cv_adc();
        char *s = new char[64];
        for(int i=0;i<N;i++){
          for(int j=0;j<18;j++){
            sprintf(s, "Device nr.%d cell voltage nr.%d voltage: %f", i, j, adbms.convert_voltage(data[i][j]));
            Serial.println(s);
          }
        }
        for(int i=0;i<N;i++){
          delete[] data[i];
        }
        delete[] data;
        delete[] s;
        break;  
      }
        
      case '1':{
        data = adbms.read_aux_adc();
        char *s = new char[64];
        for(int i=0;i<N;i++){
          for(int j=0;j<9;j++){
            sprintf(s, "Device nr.%d cell voltage nr.%d voltage: %f", i, j, adbms.convert_voltage(data[i][j]));
            Serial.println(s);
          }
        }
        for(int i=0;i<N;i++){
          delete[] data[i];
        }
        delete[] data;
        delete[] s;
        break; 
      }
      case 'q':
        write_state = true;
        display_state = 0;
        break;
      default:
        break;
    }
  }
}

void adbms_config_window(){
  if(write_state){
    write_state = false;
    Serial.println();
    Serial.println("0: Config A               1: Config B");
    Serial.println("2: Enable DCC             3: Disable DCC");
    Serial.println("q: Quit");
  }
  if(Serial.available()>0){
    char c = Serial.read();
    switch (c){
      case '1':
        adbms.set_config_reg_a();
        Serial.println("Config Reg A set");
      break;
      case '2':
        adbms.set_config_reg_b();
        Serial.println("Config Reg B set");
      break;
      case '3':
        Serial.println("DCC enabled");
        adbms.enable_dcc();
      break;
      case '4':
        Serial.println("DCC disabled");
        adbms.disable_dcc();
      break;
      case 'q':
        write_state = true;
        display_state = 0;
      break;
      default:
      break;
    }
  }
}
void adbms_balance_options(){
    char c = Serial.read();
    switch(c){
      case '0':
        adbms.write_sct_reg();
      break;
      case '1':
        adbms.write_pwm_reg();
      break;
      case '2':
        balance_state = 1;
      break;
      case '3':
        balance_state = 2;
      break;
      case 'q':
        display_state = 0;
        write_state = true;
      break;
      default:
      break;
    }
}

void adbms_sctl(){
  switch(sctl_pwm_state){
    case 0:
      Serial.println("Choose device: ");
      sctl_pwm_state = 1;
      break;
    case 1:
      n_sctl_pwm = (uint8_t)Serial.parseInt();
      if(n_sctl_pwm != 0){
        sctl_pwm_state = 2;
      }
      break;
    case 2:
      Serial.println("Choose pin: ");
      pin_sctl_pwm = (uint8_t)Serial.parseInt();
      if(pin_sctl_pwm != 0){
        sctl_pwm_state = 3;
      }
      break;
    case 3:
      Serial.println("Set value: ");
      value_sctl_pwm = (uint8_t)Serial.parseInt();
      if(value_sctl_pwm != 0){
        sctl_pwm_state = 4;
      }
      break;
    case 4:{
      char *s  = new char [32];
      sprintf(s, "N: %u Pin: %u Value: %u", (unsigned) n_sctl_pwm, (unsigned) pin_sctl_pwm, (unsigned) (value_sctl_pwm - 1));
      Serial.println(s);
      adbms.set_sct_pin_value((value_sctl_pwm - 1), pin_sctl_pwm, (n_sctl_pwm - 1));
      sctl_pwm_state = 0;
      balance_state = 0;
      write_state = true;
      delete [] s;
      break;
    }
    default:
      break;
  }
}
void adbms_pwm(){
  switch(sctl_pwm_state){
    case 0:
      Serial.println("Choose device: ");
      sctl_pwm_state = 1;
      break;
    case 1:
      n_sctl_pwm = (uint8_t)Serial.parseInt();
      if(n_sctl_pwm != 0){
        sctl_pwm_state = 2;
      }
      break;
    case 2:
      Serial.println("Choose pin: ");
      pin_sctl_pwm = (uint8_t)Serial.parseInt();
      if(pin_sctl_pwm != 0){
        sctl_pwm_state = 3;
      }
      break;
    case 3:
      Serial.println("Set value: ");
      value_sctl_pwm = (uint8_t)Serial.parseInt();
      if(value_sctl_pwm != 0){
        sctl_pwm_state = 4;
      }
      break;
    case 4:{
      char *s  = new char [32];
      sprintf(s, "N: %u Pin: %u Value: %u", (unsigned) n_sctl_pwm, (unsigned) pin_sctl_pwm, (unsigned) (value_sctl_pwm - 1));
      Serial.println(s);
      adbms.set_pwm_pin_value((value_sctl_pwm - 1), pin_sctl_pwm, (n_sctl_pwm - 1));
      sctl_pwm_state = 0;
      balance_state = 0;
      write_state = true;
      delete [] s;
      break;
    }
    default:
      break;
  }
}
void adbms_balance_window(){
  if(write_state){
    write_state = false;
    Serial.println();
    Serial.println("0: Write SCTL reg         1: Write PWM reg");
    Serial.println("2: Set SCTL pin value     3: Set PWM pin value");
    Serial.println("q: Quit");
  }
  if(Serial.available() > 0){
    switch(balance_state){
      case 0:
      adbms_balance_options();
      break;
      case 1:
      adbms_sctl();
      break;
      case 2: 
      adbms_pwm();
      break;
      default:
      break;
    }
  }
}

void ina_config_window(){
  if(write_state){
    write_state = false;
    Serial.println();
    Serial.println("0: Config 1               1: Config ADC 2");
    Serial.println("2: Config Currlsbcalc 3   3: Device found");
    Serial.println("q: Quit");
  }
  if(Serial.available() > 0){
    char c = Serial.read();
    switch(c){
      case '0':
      ina.write_config1();
      Serial.println("Config 1 set");
      break;
      case '1':
      ina.write_adc_config2();
      Serial.println("Config ADC 2 set");
      break;
      case '2':
      ina.write_currlsbcalc_3();
      Serial.println("Config currlsbcalc 3 set");
      break;
      case '3':
      if(ina.device_found()){
        Serial.println("INA238 found");
      }else{
        Serial.println("INA238 doesnt found");
      }
      break;
      case 'q':
        display_state = 0;
        write_state = true;
      break;
      default:
      break;
    }
  }
}

void ina_reads_window(){
  if(write_state){
    write_state = false;
    Serial.println();
    Serial.println("0: Current                q: Quit");
  }
  if(Serial.available() > 0){
    char c = Serial.read();
    switch(c){
      case '0':{
        float curr = ina.read_current();
        char *s = new char[32];
        sprintf(s, "Total currency: %f Amperes", curr);
        Serial.println(s);
        delete[] s;
        break;
      }
      case 'q':
        display_state = 0;
        write_state = true;
      break;
      default:
      break;
    }
  }
}