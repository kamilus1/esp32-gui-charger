#include "lvgl.h"

namespace gui{
    void init_button(lv_obj_t *btn);
    void init_label(lv_obj_t * label, lv_obj_t *parent, const char *text);
    void init_grid(lv_obj_t *cont, const lv_coord_t col[], const lv_coord_t rows[], lv_coord_t w = 320, lv_coord_t h = 240);
}