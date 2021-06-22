#include <Arduino.h>
#include <stdio.h>
#include "ADBMS1818Class.hpp"
#include "ina238.hpp"
#include <lvgl.h>
#include <Adafruit_STMPE610.h>
#include "TouchScreen.h"
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
const int8_t gui_cs=15, dc=2, rst=4;
const int8_t gui_mosi=13, gui_miso=12, gui_sck=14;
const int8_t touch_cs = 17;
Adafruit_ILI9341 tft = Adafruit_ILI9341(gui_cs, dc, gui_mosi, gui_sck, rst, gui_miso);
Adafruit_STMPE610 ts = Adafruit_STMPE610(touch_cs, gui_mosi, gui_miso, gui_sck);
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
//lvgt gui vars
static const uint16_t screen_width  = 320;
static const uint16_t screen_height = 240;
TS_Point old_point;
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf[screen_width*10];
lv_disp_drv_t disp_drv;
lv_indev_drv_t indev_drv;
lv_obj_t *btn1;
lv_obj_t *btn2;
lv_obj_t *screen_main;
lv_obj_t *label; 

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data);
void my_disp_init();
void my_input_init();

void setup() {
  Serial.begin(BAUD_RATE);
  //setup PWM
  ledcSetup(pwm_channel, freq, resolution);
  for(uint8_t i=0; i<3;i++){
    ledcAttachPin(pwm_pins[i], pwm_channel);
  }

  pinMode(CS, OUTPUT);
  
 
  // put your setup code here, to run once:
  adbms.begin();
  if(ts.begin()){
    Serial.println("Touchscreen started");
  }else{
    Serial.println("Cant start touchscreen");
  }
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(ILI9341_CYAN);
  analogReadResolution(10);
  //old_point = ts.getPoint();
  /*
  lv_init();
  lv_disp_draw_buf_init(&disp_buf, buf, NULL, screen_width * 10);
  my_disp_init();
  my_input_init();

  label = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
  lv_label_set_recolor(label, true);
  lv_label_set_text(label, "Press a button");
  lv_obj_align(label, LV_ALIGN_CENTER,0, -40);
  lv_obj_set_width(label, 150);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_pos(label, 0, 15);
  */
}




void loop() {
  if (!ts.bufferEmpty()){
    TS_Point p = ts.getPoint();
    Serial.print(p.x);
    Serial.print(":");
    Serial.println(p.y);
    delay(200);
  }
    
}
void my_input_init(){
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_input_read;
  lv_indev_drv_register(&indev_drv);
}

void my_disp_init(){
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res  = screen_height;
  disp_drv.ver_res  = screen_width;
  disp_drv.flush_cb = my_disp_flush; 
  disp_drv.draw_buf   = &disp_buf;
  lv_disp_drv_register(&disp_drv);
}


void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p){
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    uint32_t wh = w*h;
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    while (wh--) tft.pushColor(color_p++->full);
    tft.endWrite();
    lv_disp_flush_ready(disp);
}

void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
  if (!ts.bufferEmpty()){
    TS_Point p = ts.getPoint();
    data->state = LV_INDEV_STATE_PR;
    data->point.x = p.x*240/1024;
    data->point.y = p.y*320/1024;
    old_point.x = p.x;
    old_point.y = p.y;
  }
  else {
    data->state = LV_INDEV_STATE_REL;
    data->point.x = old_point.x*240/1024;
    data->point.y = old_point.y*320/1024;
  }

  
}