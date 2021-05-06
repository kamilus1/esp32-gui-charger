#include <Arduino.h>
#include "GUIslice.h"
#include "ADBMS1818.hpp"
ADBMS1818 adbms(5);
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