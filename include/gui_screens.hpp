#include "gui_renders.hpp"
#include "user_defines.h"
#include "ADBMS1818Class.hpp"
#include "ina238.hpp"
#include <vector>
#include <cstring>

namespace gui{
    //gui state
    static uint8_t state;
    static uint32_t tot_cell_qnt;
    static float sum_cell_volt;
    static int temperature;
    static float input_voltage;
    static int max_power; //whats the formula of max power? Is it DC input voltage * max_current or is it fixed? 

    //styles
    static lv_color_t main_buttons_colors[6] 
        {
        LV_COLOR_MAKE(110,210,70),  // CHARGE button 
        LV_COLOR_MAKE(255,200,80),  // STORE button 
        LV_COLOR_MAKE(255,120,80),  // DISCHG button 
        LV_COLOR_MAKE(140,200,255), // DATA button 
        LV_COLOR_MAKE(188,168,188), // CYCLE button 
        LV_COLOR_MAKE(185,190,155)  // SETTINGS button
        };
    static lv_style_t main_buttons_pr_styles[6];
    static lv_style_t main_buttons_styles[6];
    static lv_style_t main_screen_style;
    static lv_style_t process_label_style;
    static lv_style_t info_cont_style;
    static lv_style_t basic_label_style;
    static lv_style_t error_label_style;

    
    void init_styles();
    void init_main_scr_style();
    void init_main_btn_style();
    void init_main_btn_pr_style();
    void init_prc_lbl_style();
    void init_info_cnt_style();
    void init_basic_label_style();
    void init_error_label_style();



    //event handlers
    static void conversion_handler(lv_event_t *e);
    static void total_cells_handler(lv_event_t *e);
    static void charge_scr_switch_handler(lv_event_t *e);
    static void store_scr_switch_handler(lv_event_t *e);
    static void disch_scr_switch_handler(lv_event_t *e);
    static void cycle_scr_switch_handler(lv_event_t *e);
    static void process_back_handler(lv_event_t *e);

    //screens
    static lv_obj_t *curr_scr;
    static lv_obj_t *trans_scr;
    static lv_obj_t *label_conv;
    static lv_obj_t *label_cell_qnt;
    static lv_obj_t *label_cell_volt_temp;
    static lv_obj_t *label_input_electricity;
    void init_demo_screen();
    void init_start_screen();
    void init_process_screen(uint8_t process_type = CHARGE_PROCESS);
    void init_start_process_screen(uint8_t process_type = CHARGE_PROCESS);
    void init_data_list_screen();
    void init_data_candles_screen();
    void init_data_process_graph();
    void init_transition_screen();
    void load_transition();
    void load_current();

    //tasks
    static lv_timer_t *adbms_read;

    void adbms_start_scr_read(lv_timer_t *timer);
    void init_adbms_task();
};