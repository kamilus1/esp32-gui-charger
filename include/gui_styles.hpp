#include <lvgl.h>

namespace gui{
    static lv_style_t button_pr_style;
    static lv_style_t button_style;
    static lv_font_t font_style;
    void init_styles();
    void init_button_style();
    void init_button_pr_style();
    void init_button_tr_style();
    void init_font_style();
};