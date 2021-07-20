#include "gui_renders.hpp"
#include "user_defines.h"
#include "ADBMS1818Class.hpp"
#include "ina238.hpp"
#include <vector>
#include <cstring>

namespace gui{
    //styles
    static lv_palette_t main_buttons_colors[6] {LV_PALETTE_GREEN, LV_PALETTE_YELLOW, LV_PALETTE_RED, LV_PALETTE_BLUE, 
    LV_PALETTE_PURPLE, LV_PALETTE_GREY};
    static lv_style_t main_buttons_pr_styles[6];
    static lv_style_t main_buttons_styles[6];
    static lv_style_t main_screen_style;
    static lv_style_t process_label_style;

    static uint8_t state;

    void init_styles();
    void init_main_scr_style();
    void init_main_btn_style();
    void init_main_btn_pr_style();
    void init_prc_lbl_style();



    //event handlers
    static void conversion_handler(lv_event_t *e);
    static void total_cells_handler(lv_event_t *e);
    static void charge_scr_switch_handler(lv_event_t *e);
    static void store_scr_switch_handler(lv_event_t *e);
    static void disch_scr_switch_handler(lv_event_t *e);
    static void cycle_scr_switch_handler(lv_event_t *e);
    static void process_back_handler(lv_event_t *e);


    static lv_obj_t *curr_scr;
    static lv_obj_t *trans_scr;
    static lv_obj_t *label_conv;
    static lv_obj_t *label_cell_qnt;
    void init_demo_screen();
    void init_start_screen();
    void init_process_screen(uint8_t process_type = CHARGE_PROCESS);
    void init_transition_screen();
    void load_transition();
    void load_current();

};