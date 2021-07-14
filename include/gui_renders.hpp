#include <lvgl.h>
#include "gui_styles.hpp"

namespace gui{
    void init_button(lv_obj_t *btn, lv_obj_t *parent, lv_event_cb_t event);
    void init_label(lv_obj_t * label, lv_obj_t *parent, const char *text);
}