#include <lvgl.h>

namespace gui{
    void init_button(lv_obj_t *button, lv_style_t *style, lv_style_t *style_pr, 
    lv_coord_t x, lv_coord_t y, lv_coord_t w=1, lv_coord_t h=1);
    void init_cont(lv_obj_t *cont, lv_style_t *style, lv_coord_t x, lv_coord_t y, lv_coord_t w=1, lv_coord_t h=1);
    void init_label(lv_obj_t * label, lv_obj_t *parent, const char *text);
    void init_grid(lv_obj_t *cont, const lv_coord_t col[], const lv_coord_t rows[], lv_coord_t w = 320, lv_coord_t h = 240);
    void init_bar(lv_obj_t *bar, lv_style_t *indic_style, lv_style_t *main_style, lv_coord_t w=15, lv_coord_t h=120);
}