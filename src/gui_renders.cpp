#include "gui_renders.hpp"


namespace gui{
    void init_button(lv_obj_t *button, lv_style_t *style, lv_style_t *style_pr, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h){                                                                                                                                            
        lv_obj_add_style(button, style, LV_STATE_DEFAULT);
        lv_obj_add_style(button, style_pr, LV_STATE_PRESSED);
        lv_obj_set_grid_cell(button, LV_GRID_ALIGN_STRETCH, x, w, LV_GRID_ALIGN_STRETCH, y, h);
    }

    void init_label(lv_obj_t * label, lv_obj_t *parent, const char *text){
        label = lv_label_create(parent);
        lv_obj_remove_style_all(label);
        lv_label_set_text(label, text);
    }

    void init_cont(lv_obj_t *cont, lv_style_t *style, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h){
        lv_obj_add_style(cont, style, LV_STATE_DEFAULT);
        lv_obj_set_grid_cell(cont, LV_GRID_ALIGN_STRETCH, x, w, LV_GRID_ALIGN_STRETCH, y, h);
    }

    void init_grid(lv_obj_t *cont, const lv_coord_t col[], const lv_coord_t rows[], lv_coord_t w, lv_coord_t h){
        lv_obj_set_grid_align(cont, LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_END);
        
        lv_obj_set_grid_dsc_array(cont, col, rows);
        lv_obj_set_size(cont, w, h);
        lv_obj_center(cont);
    }

    void init_bar(lv_obj_t *bar, lv_style_t *indic_style, lv_style_t *main_style, lv_coord_t w, lv_coord_t h){
        lv_obj_remove_style_all(bar);
        lv_obj_add_style(bar, main_style, LV_PART_MAIN);
        lv_obj_add_style(bar, indic_style, LV_PART_INDICATOR);
        lv_obj_set_size(bar, w, h);
        lv_bar_set_value(bar, 0, LV_ANIM_ON);
        
        lv_obj_center(bar);
    }

    void init_info_label(lv_obj_t *grid, lv_obj_t *label, lv_style_t *style, lv_coord_t w, lv_coord_t h){
        lv_obj_t *info_cont = lv_obj_create(grid);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, style, 0, 0, 5);
        label = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label, "0-S BAT DETECTED 0.0V 0°C");
    }
    void init_data_buttons(lv_obj_t *grid, lv_style_t **styles,  lv_style_t **pr_styles, lv_coord_t *xs, lv_event_cb_t *cbs, lv_coord_t y, lv_coord_t w, lv_coord_t h){
        try{
            lv_obj_t *back_btn = lv_btn_create(grid);
            lv_obj_t *data_btn = lv_btn_create(grid);
            lv_obj_t *prev_btn = lv_btn_create(grid);
            lv_obj_t *next_btn = lv_btn_create(grid);
            init_button(back_btn, styles[0], pr_styles[0], xs[0], y, w);
            init_button(data_btn, styles[1], pr_styles[1], xs[1], y, w);
            init_button(prev_btn, styles[2], pr_styles[2], xs[2], y, w);
            init_button(next_btn, styles[2], pr_styles[2], xs[3], y, w);
            lv_obj_add_event_cb(back_btn, cbs[0], LV_EVENT_CLICKED, NULL);
            lv_obj_add_event_cb(next_btn, cbs[1], LV_EVENT_CLICKED, NULL);
            lv_obj_add_event_cb(prev_btn, cbs[2], LV_EVENT_CLICKED, NULL);
            lv_obj_add_event_cb(data_btn, cbs[3], LV_EVENT_CLICKED, NULL);
        }catch(const std::exception &e){

        }
        
    }
};