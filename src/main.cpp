#include <Arduino.h>
#include <stdio.h>
#include <SPI.h>
#include <Wire.h>

#include <TFT_eSPI.h>

#include <lvgl.h>



#include "ADBMS1818Class.hpp"
#include "ina238.hpp"



#define BAUD_RATE 115200
#define N 1
#define CS 5
#define TOUCH_IRQ 16

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
static const uint32_t screenWidth  = 240;
static const uint32_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t*data);
//void my_disp_init();
//void my_input_init();
static void event_handler(lv_event_t *e);
void lv_example_btn_2();
uint16_t touchX, touchY;

void setup() {
  Serial.begin(BAUD_RATE);
  //setup PWM
  ledcSetup(pwm_channel, freq, resolution);
  for(uint8_t i=0; i<3;i++){
    ledcAttachPin(pwm_pins[i], pwm_channel);
  }
  
  pinMode(CS, OUTPUT);
  pinMode(TOUCH_IRQ, INPUT);
  tft.init();
  tft.setRotation(0);
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
   //create simple label
    lv_example_btn_2();
    

}




void loop() {
    lv_timer_handler();
    delay(5);
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

void lv_example_btn_2(void)
{
    /*Init the style for the default state*/
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, 3);

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&style, LV_OPA_40);
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&style, 8);
    lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_ofs_y(&style, 8);

    lv_style_set_outline_opa(&style, LV_OPA_COVER);
    lv_style_set_outline_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_pad_all(&style, 10);

    /*Init the pressed style*/
    static lv_style_t style_pr;
    lv_style_init(&style_pr);

    /*Ad a large outline when pressed*/
    lv_style_set_outline_width(&style_pr, 30);
    lv_style_set_outline_opa(&style_pr, LV_OPA_TRANSP);

    lv_style_set_translate_y(&style_pr, 5);
    lv_style_set_shadow_ofs_y(&style_pr, 3);
    lv_style_set_bg_color(&style_pr, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_color(&style_pr, lv_palette_darken(LV_PALETTE_BLUE, 4));

    /*Add a transition to the the outline*/
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA,(lv_style_prop_t) 0};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_set_transition(&style_pr, &trans);

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    lv_obj_remove_style_all(btn1);
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn1, &style, 0);
    lv_obj_add_style(btn1, &style_pr, LV_STATE_PRESSED);
    lv_obj_set_size(btn1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(btn1);

    lv_obj_t * label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);
}