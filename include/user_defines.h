

#define ADBMS_AMOUNT 1
#define ADBMS_ADC_RESOLUTION 16
#define CS 5

#define TOUCH_THRESHOLD 600



#define VERSION 1.0

#define CHARGE_PROCESS 0
#define STORE_PROCESS 1
#define DISCHARGE_PROCESS 2
#define CYCLE_PROCESS 3
//ina238 driver
//address depends on signals attached to A0 and A1 pins of ina238. 
//https://www.ti.com/lit/ds/symlink/ina238-q1.pdf?ts=1623446444912#page=15
#define INA238_ADDR 0x40
#define INA238_RSHUNT 0.002 // in ohms


#define ADBMS_READ_PERIOD 500 //500 ms 
#define PROCESS_READ_PERIOD 1000 //1000 ms 
#define MAX_CURRENT 25 //In amperes
#define MAX_CHG_TEMP 90 //in degrees
#define IPRE 1.0

