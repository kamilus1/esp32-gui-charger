#include <Arduino.h>
#include "GUIslice.h"
#include "ADBMS1818.hpp"
int8_t pins = {14,12,13,15};//tab for custom SPI Pins. sck, miso, mosi, cs is a pin order. In this tab i use HSPI port SPI pins
ADBMS1818 adbms(pins);
uint16_t cells_voltage[18];
void setup() {
  // put your setup code here, to run once:
  adbms.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t *cv = adbms.read_cv_adc(cells_voltage);
  delay(1000);
}