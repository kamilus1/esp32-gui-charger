#include <Arduino.h>
#include <stdio.h>
#include "GUIslice.h"
#include "ADBMS1818.hpp"
#define BAUD_RATE 115200
#define N 1
int8_t pins[4] = {14,12,13,15};//tab for custom SPI Pins. sck, miso, mosi, cs is a pin order. In this tab i use HSPI port SPI pins
//ADBMS1818 adbms(pins); //constructor with modified pins
ADBMS1818 adbms((uint8_t)VSPI, (uint8_t)5); //construcot with modified CS pin and spi port
//ADBMS1818 adbms(15); //constructor with default SPI and CS pin modifed
void setup() {
  pinMode(cs, OUTPUT);
  // put your setup code here, to run once:
  adbms.set_device_count(N);
  Serial.begin(BAUD_RATE);
  adbms.begin();
}
/*simple interface for choosing operation. 
0 - start_cv_adc_conversion
1 - start_open_wire_conversion
2 - start_self_test_conversion
3 - start_overlap_conversion
4 - start_gpio_adc_conversion
5 - start_gpio_adc_conversion_dr
6 - start_gpio_open_wire_conversion
7 - start_self_test_gpio_conversion
8 - start_status_adc_conversion
9 - start_status_adc_dr_conversion
a - start_self_test_status_conversion
b - start_cv_gpio12_conversion
c - start_cv_sc_conversion
d - read_cv_adc
e - read_aux_adc
f - pladc_rdy (this command returns true if conversion is ready)
*/
void loop() {
  // put your main code here, to run repeatedly:
  uint16_t **data;
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
      case 'd':{
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
      case 'e':{
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
      case 'f':
        if(adbms.pladc_rdy()){
          Serial.println("Conversion done!");
        }else{
          Serial.println("Conversion not done!");
        }
        break;     
      default:
        break;       
    }
  }
  
}