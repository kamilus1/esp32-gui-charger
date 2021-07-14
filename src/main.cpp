#include <Arduino.h>
#include <stdio.h>
#include <SPI.h>
#include <Wire.h>

#include <TFT_eSPI.h>

#include <lvgl.h>

#include "gui_screens.hpp"


#define BAUD_RATE 115200
#define N 1
#define CS 5

#define TOUCH_THRESHOLD 600

//pwm variables
const int freq = 10000; //10 khz
const int pwm_channel = 0;
const int resolution = 12; //12 bit resolution
//gui variables

TFT_eSPI tft = TFT_eSPI();

//pwm pins
const int8_t pwm_pins[3] = {25, 26, 27};
//adbms pins and object
int8_t adbms_pins[4] = {18,19,23,CS};//tab for custom SPI Pins. sck, miso, mosi, cs is a pin order. In this tab i use HSPI port SPI pins
ADBMS1818Class adbms = ADBMS1818Class(adbms_pins); //constructor with modified pins
//ADBMS1818 adbms((uint8_t)FSPI, (uint8_t)CS); //construcot with modified CS pin and spi port
//ADBMS1818 adbms(15); //constructor with default SPI and CS pin modifed
//ina238 driver
//address depends on signals attached to A0 and A1 pins of ina238. 
//https://www.ti.com/lit/ds/symlink/ina238-q1.pdf?ts=1623446444912#page=15
ina238 ina((uint16_t)0x40);
//lvgt gui vars
static const uint32_t screenWidth  = 320;
static const uint32_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t*data);
static void event_handler(lv_event_t *e);
uint16_t touchX, touchY;




void setup() {
  Serial.begin(BAUD_RATE);
  //setup PWM
  ledcSetup(pwm_channel, freq, resolution);
  for(uint8_t i=0; i<3;i++){
    ledcAttachPin(pwm_pins[i], pwm_channel);
  }
  
  pinMode(CS, OUTPUT);
  tft.init();
  tft.setRotation(3);
  uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
  tft.setTouch( calData );
  
  //tft.fillScreen(TFT_GREEN);
  
 
  
 
  // put your setup code here, to run once:
  adbms.begin();
  //init setup of LVGL
  
  lv_init();
  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  disp_drv.hor_res = screenWidth;
   disp_drv.ver_res = screenHeight;
   disp_drv.flush_cb = my_disp_flush;
   disp_drv.draw_buf = &draw_buf;
   lv_disp_drv_register( &disp_drv );

   //Initialize the (dummy) input device driver
   static lv_indev_drv_t indev_drv;
   lv_indev_drv_init( &indev_drv );
   indev_drv.type = LV_INDEV_TYPE_POINTER;
   indev_drv.read_cb = my_touchpad_read;
   lv_indev_drv_register( &indev_drv );

   //Initialize styles
   gui::init_demo_screen();
   gui::load_current();
    

}




void loop() {
    lv_timer_handler();
    delay(1);
}


void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p){
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

void my_touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
  uint16_t touchX, touchY;
   bool touched = tft.getTouch( &touchX, &touchY, TOUCH_THRESHOLD );
   
   if( !touched )
   {
      data->state = LV_INDEV_STATE_REL;
   }
   else
   {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touchX;
      data->point.y = touchY;
   }
}

static void event_handler(lv_event_t *e){
  lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
      Serial.println("essa");
    }
}

