#include <Arduino.h>
#include <stdio.h>
//#include "ADBMS1818Class.hpp"
#include "ina238.hpp"
//#include "lvgl.h"
//#include <Adafruit_STMPE610.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#define BAUD_RATE 115200
#define N 1
#define CS 5

//pwm variables
const int freq = 10000; //10 khz
const int pwm_channel = 0;
const int resolution = 12; //12 bit resolution
//gui variables
const int8_t gui_cs=5, dc=16, rst=4;
const int8_t gui_mosi=23, gui_miso=19, gui_sck=18;
const int8_t touch_cs = 17;
Adafruit_ILI9341 tft = Adafruit_ILI9341(gui_cs, dc, gui_mosi, gui_sck, rst, gui_miso);
//Adafruit_STMPE610 ts = Adafruit_STMPE610(touch_cs);
//pwm pins

const int8_t pwm_pins[3] = {25, 26, 27};

//adbms pins and object
int8_t adbms_pins[4] = {18,19,23,CS};//tab for custom SPI Pins. sck, miso, mosi, cs is a pin order. In this tab i use HSPI port SPI pins
//ADBMS1818Class adbms(adbms_pins); //constructor with modified pins
//ADBMS1818 adbms((uint8_t)FSPI, (uint8_t)CS); //construcot with modified CS pin and spi port
//ADBMS1818 adbms(15); //constructor with default SPI and CS pin modifed
//ina238 driver
//address depends on signals attached to A0 and A1 pins of ina238. 
//https://www.ti.com/lit/ds/symlink/ina238-q1.pdf?ts=1623446444912#page=15
ina238 ina((uint16_t)0x40);
//serial demo variables

void setup() {
  Serial.begin(BAUD_RATE);
  //setup PWM
  ledcSetup(pwm_channel, freq, resolution);
  for(uint8_t i=0; i<3;i++){
    ledcAttachPin(pwm_pins[i], pwm_channel);
  }

  pinMode(CS, OUTPUT);
  
 
  // put your setup code here, to run once:
  //adbms.begin();
  tft.begin();
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.println(x, HEX);
  tft.fillScreen(ILI9341_BLUE);
}




void loop() {
  
    
}


