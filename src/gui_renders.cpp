#include "gui_renders.hpp"


namespace gui{
    void init_button(lv_obj_t *button){
        lv_obj_remove_style_all(button);                                                                                                                                              
        lv_obj_add_style(button, &button_style, 0);
        lv_obj_add_style(button, &button_pr_style, LV_STATE_PRESSED);
        lv_obj_set_size(button, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        
    }

    void init_label(lv_obj_t * label, lv_obj_t *parent, const char *text){
        label = lv_label_create(parent);
        lv_obj_remove_style_all(label);
        lv_label_set_text(label, text);
    }
};