#include "gui_renders.hpp"


namespace gui{
    void init_button(lv_obj_t *button, lv_obj_t *parent, lv_event_cb_t event_handler){
        button = lv_btn_create(parent);
        lv_obj_remove_style_all(button);                                                                                                                                              
        lv_obj_add_event_cb(button, event_handler, LV_EVENT_ALL, NULL);                          /*Remove the style coming from the theme*/
        lv_obj_add_style(button, &button_style, 0);
        lv_obj_add_style(button, &button_pr_style, LV_STATE_PRESSED);
        
    }

    void init_label(lv_obj_t * label, lv_obj_t *parent, const char *text){
        label = lv_label_create(parent);
        lv_obj_remove_style_all(label);
        lv_obj_set_style_text_font(label, &font_style, 0);
        lv_obj_set_text(label, text);
    }
};