#include <lvgl.h>

namespace gui{
    static lv_style_t button_pr_style;
    static lv_style_t button_style;
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[3];
    void init_styles();
    void init_button_style();
    void init_button_pr_style();
};